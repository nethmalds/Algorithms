#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

struct Round {
    int units;
    int cost;
    double efficiency;
    int index;
};

class AuctionSolver {
public:
    vector<Round> rounds;
    int n;
    int target;
    
    AuctionSolver(const vector<int>& units, int targetUnits) : target(targetUnits) {
        n = units.size();
        rounds.resize(n);
        
        // Step 1 & 2: Calculate competitor bids and our winning bids
        for (int i = 0; i < n; i++) {
            int competitorBid = units[i] / 5; // 20% rounded down (integer division)
            int ourBid = competitorBid + 1;   // We bid 1 more to win
            
            rounds[i].units = units[i];
            rounds[i].cost = ourBid;
            rounds[i].efficiency = (double)units[i] / ourBid; // units per cost
            rounds[i].index = i;
        }
    }
    
    // Step 3: Greedy selection by efficiency until we reach target
    int solve() {
        // Sort rounds by efficiency (units per cost) in descending order
        sort(rounds.begin(), rounds.end(), [](const Round& a, const Round& b) {
            if (a.efficiency != b.efficiency) {
                return a.efficiency > b.efficiency;
            }
            // If efficiency is same, prefer lower cost (or any tie-breaking rule)
            return a.cost < b.cost;
        });
        
        int totalUnits = 0;
        int totalCost = 0;
        
        // Greedily select most efficient rounds until we reach exactly target units
        for (int i = 0; i < n; i++) {
            if (totalUnits >= target) break;
            
            totalUnits += rounds[i].units;
            totalCost += rounds[i].cost;
        }
        
        // Check if we achieved the target
        if (totalUnits >= target) {
            return totalCost;
        } else {
            return -1; // Impossible to reach target
        }
    }
    
    // Alternative: Exact DP solution for verification
    int solveDP() {
        // dp[u] = minimum cost to get exactly u units
        vector<int> dp(target + 1, INT_MAX);
        dp[0] = 0;
        
        for (int i = 0; i < n; i++) {
            for (int u = target; u >= rounds[i].units; u--) {
                if (dp[u - rounds[i].units] != INT_MAX) {
                    dp[u] = min(dp[u], dp[u - rounds[i].units] + rounds[i].cost);
                }
            }
        }
        
        return dp[target] == INT_MAX ? -1 : dp[target];
    }
    
    // Debug function to show the step-by-step process like in explanation
    void debugProcess() {
        cout << "Step 1: Competitor's Bids" << endl;
        for (int i = 0; i < n; i++) {
            int competitorBid = rounds[i].units / 5;
            cout << "Round " << i << ": " << rounds[i].units 
                 << " units to Competitor bids " << competitorBid 
                 << " (20% of " << rounds[i].units << ")" << endl;
        }
        
        cout << "\nStep 2: Our Winning Bids" << endl;
        cout << "To win, we bid 1 more than competitor: [";
        for (int i = 0; i < n; i++) {
            cout << rounds[i].cost;
            if (i < n - 1) cout << ", ";
        }
        cout << "]" << endl;
        
        cout << "\nStep 3: Optimal Strategy" << endl;
        cout << "Select rounds with best efficiency (units per cost):" << endl;
        
        // Sort by efficiency for display
        vector<Round> sortedRounds = rounds;
        sort(sortedRounds.begin(), sortedRounds.end(), [](const Round& a, const Round& b) {
            return a.efficiency > b.efficiency;
        });
        
        int totalUnits = 0;
        int totalCost = 0;
        int step = 1;
        
        for (const auto& round : sortedRounds) {
            if (totalUnits >= target) break;
            
            totalUnits += round.units;
            totalCost += round.cost;
            
            cout << step << ". Round " << round.index << ": " 
                 << round.units << " units, cost " << round.cost 
                 << " (running total: " << totalUnits << " units, " 
                 << totalCost << " cost)";
            if (totalUnits >= target) cout << " DONE";
            cout << endl;
            step++;
        }
        
        cout << "\nFinal Answer: " << totalCost << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int rounds;
    cin >> rounds;
    
    vector<int> units(rounds);
    for (int i = 0; i < rounds; i++) {
        cin >> units[i];
    }
    
    const int TARGET_UNITS = 1000;
    
    AuctionSolver solver(units, TARGET_UNITS);
    
    // Use the simple greedy approach as shown in explanation
    int result = solver.solve();
    
    cout << result << endl;
    
    return 0;
}

/*
Algorithm following the exact explanation:

1. **Competitor's Bids**: Calculate 20% of available units (integer division)
2. **Our Winning Bids**: Competitor's bid + 1
3. **Optimal Strategy**: Greedy selection by efficiency (units/cost ratio)

Key insights from the explanation:
- The solution ignores the aggression mechanism completely
- Uses simple greedy approach: sort by efficiency, select until target reached
- Integer division for 20% calculation (units/5)
- No complex game theory needed

Time Complexity: O(n log n) for sorting
Space Complexity: O(n) for rounds array

This matches exactly what's shown in the provided explanation.
*/