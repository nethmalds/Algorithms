#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

vector<char> trafficController(const vector<vector<string>>& events) {
    // Initialize queue counts for each lane (A, B, C, D)
    unordered_map<char, int> lanes = {{'A', 0}, {'B', 0}, {'C', 0}, {'D', 0}};
    
    vector<char> results;
    
    // Process each event
    for (const auto& event : events) {
        if (event[0] == "EVENT") {
            // Increment the queue count for the specified lane
            lanes[event[1][0]]++;
        } else if (event[0] == "TICK") {
            // Find the lane with the longest queue
            int maxQueue = 0;
            char chosenLane = 'A'; // Default to 'A' as it has highest priority
            
            for (char lane = 'A'; lane <= 'D'; lane++) {
                if (lanes[lane] > maxQueue) {
                    maxQueue = lanes[lane];
                    chosenLane = lane;
                }
            }
            
            // Add the chosen lane to results
            results.push_back(chosenLane);
            
            // Reset the queue count for the chosen lane
            lanes[chosenLane] = 0;
        }
    }
    
    return results;
}

int main() {
    int n;
    cin >> n;
    
    vector<vector<string>> events(n);
    
    for (int i = 0; i < n; i++) {
        string eventType;
        cin >> eventType;
        
        if (eventType == "EVENT") {
            string lane;
            cin >> lane;
            events[i] = {eventType, lane};
        } else {
            events[i] = {eventType};
        }
    }
    
    vector<char> results = trafficController(events);
    
    for (char lane : results) {
        cout << lane << endl;
    }
    
    return 0;
}