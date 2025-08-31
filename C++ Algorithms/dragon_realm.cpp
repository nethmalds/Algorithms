#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    // Queues for each role (FIFO - First In, First Out)
    queue<string> damage_queue;
    queue<string> tank_queue;
    queue<string> support_queue;
    
    bool match_found = false;
    
    for (int i = 0; i < n && !match_found; i++) {
        string player_id, action, role;
        cin >> player_id >> action >> role;
        
        if (action == "QUEUE_JOIN") {
            // Enqueue: Add player to back of appropriate role queue
            if (role == "DAMAGE") {
                damage_queue.push(player_id);
            } else if (role == "TANK") {
                tank_queue.push(player_id);
            } else if (role == "SUPPORT") {
                support_queue.push(player_id);
            }
        } else if (action == "QUEUE_LEAVE") {
            // Dequeue: Remove player from front of appropriate role queue
            if (role == "DAMAGE" && !damage_queue.empty()) {
                damage_queue.pop();
            } else if (role == "TANK" && !tank_queue.empty()) {
                tank_queue.pop();
            } else if (role == "SUPPORT" && !support_queue.empty()) {
                support_queue.pop();
            }
        }
        
        // Check if we can form a team (2 DAMAGE, 2 TANK, 1 SUPPORT)
        if (damage_queue.size() >= 2 && tank_queue.size() >= 2 && support_queue.size() >= 1) {
            cout << "MATCH_FOUND";
            
            // Get the players for the team (first 2 DAMAGE, first 2 TANK, first 1 SUPPORT)
            // We need to access elements without removing them permanently
            
            // Create temporary queues to extract players
            queue<string> temp_damage = damage_queue;
            queue<string> temp_tank = tank_queue;
            queue<string> temp_support = support_queue;
            
            // Output first 2 DAMAGE players
            cout << " " << temp_damage.front(); temp_damage.pop();
            cout << " " << temp_damage.front(); temp_damage.pop();
            
            // Output first 2 TANK players
            cout << " " << temp_tank.front(); temp_tank.pop();
            cout << " " << temp_tank.front(); temp_tank.pop();
            
            // Output first SUPPORT player
            cout << " " << temp_support.front();
            
            cout << endl;
            match_found = true;
        }
    }
    
    return 0;
}