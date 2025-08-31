#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, W;
    cin >> n >> W;
    
    vector<int> weight(n), value(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }
    
    // Use 2D DP for clarity and correctness
    // dp[i][w] = maximum value using first i items with weight limit w
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            // Don't take item i-1
            dp[i][w] = dp[i-1][w];
            
            // Take item i-1 if it fits
            if (w >= weight[i-1]) {
                dp[i][w] = max(dp[i][w], dp[i-1][w - weight[i-1]] + value[i-1]);
            }
        }
    }
    
    cout << dp[n][W] << endl;
    
    return 0;
}

/*
Alternative Space-Optimized Version (if memory is a concern):

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, W;
    cin >> n >> W;
    
    vector<int> weight(n), value(n);
    for (int i = 0; i < n; i++) {
        cin >> weight[i] >> value[i];
    }
    
    vector<int> dp(W + 1, 0);
    
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= weight[i]; w--) {
            dp[w] = max(dp[w], dp[w - weight[i]] + value[i]);
        }
    }
    
    cout << dp[W] << endl;
    return 0;
}

Classic 2D DP Approach - Most Reliable:
- dp[i][w] = maximum value using first i items with weight capacity w
- This eliminates any potential issues with the 1D optimization
- The 2D version is more straightforward and less error-prone

Time Complexity: O(n * W) 
Space Complexity: O(n * W)

The 2D approach is the gold standard for knapsack problems and should handle all edge cases correctly.
*/