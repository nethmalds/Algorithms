#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;

struct Edge {
    int to;
    int travel_time;
    int closure_start;
    int closure_end;
    
    Edge(int t, int tt, int cs, int ce) 
        : to(t), travel_time(tt), closure_start(cs), closure_end(ce) {}
};

struct State {
    int node;
    int time;
    
    State(int n, int t) : node(n), time(t) {}
    
    bool operator>(const State& other) const {
        return time > other.time;
    }
};

class EmergencyDispatch {
private:
    vector<vector<Edge>> graph;
    int n;
    
    // Check if we can start traversing an edge at given time
    bool canTraverse(const Edge& edge, int current_time) {
        // If no closure, always can traverse
        if (edge.closure_start == -1) return true;
        
        int finish_time = current_time + edge.travel_time;
        
        // Road must be open for the entire duration [current_time, finish_time)
        // Check if closure period [closure_start, closure_end] intersects with travel period
        return !(edge.closure_start < finish_time && edge.closure_end >= current_time);
    }
    
public:
    EmergencyDispatch(int nodes) : n(nodes) {
        graph.resize(n + 1);
    }
    
    void addEdge(int u, int v, int travel_time, int closure_start, int closure_end) {
        graph[u].emplace_back(v, travel_time, closure_start, closure_end);
        graph[v].emplace_back(u, travel_time, closure_start, closure_end);
    }
    
    int findMinTime(int start_time, int target) {
        // Priority queue for Dijkstra's algorithm (min-heap based on time)
        priority_queue<State, vector<State>, greater<State>> pq;
        
        // Distance array - minimum time to reach each node
        vector<int> dist(n + 1, numeric_limits<int>::max());
        
        // Start from node 1 at start_time
        pq.emplace(1, start_time);
        dist[1] = start_time;
        
        while (!pq.empty()) {
            State current = pq.top();
            pq.pop();
            
            int curr_node = current.node;
            int curr_time = current.time;
            
            // If we reached target, return travel time
            if (curr_node == target) {
                return curr_time - start_time;
            }
            
            // Skip if we already found a better path to this node
            if (curr_time > dist[curr_node]) continue;
            
            // Explore all adjacent edges
            for (const Edge& edge : graph[curr_node]) {
                // Check if we can traverse this edge at current time
                if (!canTraverse(edge, curr_time)) continue;
                
                int new_time = curr_time + edge.travel_time;
                
                // If we found a better path to the neighbor
                if (new_time < dist[edge.to]) {
                    dist[edge.to] = new_time;
                    pq.emplace(edge.to, new_time);
                }
            }
        }
        
        // No path found
        return -1;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m, start_time, accident_node;
    cin >> n >> m >> start_time >> accident_node;
    
    EmergencyDispatch dispatcher(n);
    
    for (int i = 0; i < m; i++) {
        int u, v, travel_time, closure_start, closure_end;
        cin >> u >> v >> travel_time >> closure_start >> closure_end;
        dispatcher.addEdge(u, v, travel_time, closure_start, closure_end);
    }
    
    int result = dispatcher.findMinTime(start_time, accident_node);
    cout << result << endl;
    
    return 0;
}