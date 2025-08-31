#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <climits>

using namespace std;

class SalesAgent {
private:
    // Memoization cache: key = (day, budget, sales), value = max_total_sales
    unordered_map<long long, long long> memo;
    
    // Create unique key for memoization
    long long createKey(int day, int budget, long long sales) {
        // Use bit shifting to create unique key
        // Assuming sales won't exceed 10^12 (48 bits), budget max 100 (7 bits), day max 30 (5 bits)
        return ((long long)day << 55) | ((long long)budget << 48) | sales;
    }
    
    long long solve(int day, int budget, long long currentSales) {
        // Base case: if we're past day 30, return 0
        if (day > 30) {
            return 0;
        }
        
        // Check memoization
        long long key = createKey(day, budget, currentSales);
        if (memo.find(key) != memo.end()) {
            return memo[key];
        }
        
        long long maxTotal = 0;
        
        // Try all three actions
        
        // 1. DECREASE action (costs 5 budget, +50% next day sales)
        if (budget >= 5) {
            long long nextSales = currentSales + (currentSales * 50) / 100;
            long long total = currentSales + solve(day + 1, budget - 5, nextSales);
            maxTotal = max(maxTotal, total);
        }
        
        // 2. INCREASE action (free, -20% next day sales)
        long long nextSalesIncrease = currentSales - (currentSales * 20) / 100;
        long long totalIncrease = currentSales + solve(day + 1, budget, nextSalesIncrease);
        maxTotal = max(maxTotal, totalIncrease);
        
        // 3. HOLD action (free, no change in next day sales)
        long long totalHold = currentSales + solve(day + 1, budget, currentSales);
        maxTotal = max(maxTotal, totalHold);
        
        // Store in memo and return
        memo[key] = maxTotal;
        return maxTotal;
    }
    
public:
    long long salesAgent(int initialSales, int initialBudget) {
        memo.clear();
        return solve(1, initialBudget, initialSales);
    }
};

int main() {
    int initialSales, initialBudget;
    cin >> initialSales >> initialBudget;
    
    SalesAgent agent;
    cout << agent.salesAgent(initialSales, initialBudget) << endl;
    
    return 0;
}

// Alternative iterative approach for better memory efficiency with very large inputs
class SalesAgentIterative {
private:
    struct State {
        int budget;
        long long sales;
        long long totalSales;
        
        bool operator<(const State& other) const {
            if (budget != other.budget) return budget < other.budget;
            if (sales != other.sales) return sales < other.sales;
            return totalSales < other.totalSales;
        }
    };
    
public:
    long long salesAgent(int initialSales, int initialBudget) {
        // Use bottom-up DP with space optimization
        // dp[budget][sales_tier] = max_remaining_sales
        
        // Since sales can grow exponentially, we need to be smart about state space
        vector<unordered_map<long long, long long>> dp(initialBudget + 1);
        vector<unordered_map<long long, long long>> nextDp(initialBudget + 1);
        
        // Initialize for day 30 (base case)
        for (int b = 0; b <= initialBudget; b++) {
            dp[b][0] = 0; // No more days, no more sales
        }
        
        // Work backwards from day 29 to day 1
        for (int day = 29; day >= 1; day--) {
            // Clear next day's DP
            for (int b = 0; b <= initialBudget; b++) {
                nextDp[b].clear();
            }
            
            for (int budget = 0; budget <= initialBudget; budget++) {
                for (auto& [sales, remainingSales] : dp[budget]) {
                    if (sales == 0 && day > 1) continue; // Skip invalid states
                    
                    long long currentDaySales = (day == 1) ? initialSales : sales;
                    long long maxFromThisState = 0;
                    
                    // Try DECREASE action
                    if (budget >= 5) {
                        long long nextSales = currentDaySales + (currentDaySales * 50) / 100;
                        if (dp[budget - 5].find(nextSales) != dp[budget - 5].end()) {
                            maxFromThisState = max(maxFromThisState, 
                                currentDaySales + dp[budget - 5][nextSales]);
                        }
                    }
                    
                    // Try INCREASE action
                    long long nextSalesInc = currentDaySales - (currentDaySales * 20) / 100;
                    if (dp[budget].find(nextSalesInc) != dp[budget].end()) {
                        maxFromThisState = max(maxFromThisState, 
                            currentDaySales + dp[budget][nextSalesInc]);
                    }
                    
                    // Try HOLD action
                    if (dp[budget].find(currentDaySales) != dp[budget].end()) {
                        maxFromThisState = max(maxFromThisState, 
                            currentDaySales + dp[budget][currentDaySales]);
                    }
                    
                    nextDp[budget][sales] = max(nextDp[budget][sales], maxFromThisState);
                }
            }
            
            // Swap DP arrays
            dp.swap(nextDp);
        }
        
        // Find maximum from initial state
        return dp[initialBudget][initialSales];
    }
};

// Optimized recursive solution with pruning
long long optimizedSalesAgent(int initialSales, int initialBudget) {
    SalesAgent agent;
    return agent.salesAgent(initialSales, initialBudget);
}