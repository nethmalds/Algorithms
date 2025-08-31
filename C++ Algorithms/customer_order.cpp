#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<string>> dailySummary(const vector<pair<string, int>>& orders) {
    // Use unordered_map for O(1) average case lookup and insertion
    unordered_map<string, int> customerTotals;
    
    // Aggregate totals for each customer - O(n)
    for (const auto& order : orders) {
        customerTotals[order.first] += order.second;
    }
    
    // Convert to result format - O(unique customers)
    vector<vector<string>> result;
    result.reserve(customerTotals.size()); // Pre-allocate for efficiency
    
    for (const auto& customer : customerTotals) {
        result.push_back({customer.first, to_string(customer.second)});
    }
    
    // Sort alphabetically by customer name - O(k log k) where k = unique customers
    sort(result.begin(), result.end(), [](const vector<string>& a, const vector<string>& b) {
        return a[0] < b[0];
    });
    
    return result;
}

int main() {
    ios_base::sync_with_stdio(false); // Faster I/O
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    
    vector<pair<string, int>> orders;
    orders.reserve(n); // Pre-allocate memory
    
    string customerName;
    int itemCount;
    
    for (int i = 0; i < n; i++) {
        cin >> customerName >> itemCount;
        orders.emplace_back(customerName, itemCount);
    }
    
    vector<vector<string>> summary = dailySummary(orders);
    
    // Output in the required format
    cout << "[";
    for (size_t i = 0; i < summary.size(); i++) {
        cout << "[\"" << summary[i][0] << "\", " << summary[i][1] << "]";
        if (i < summary.size() - 1) {
            cout << ", ";
        }
    }
    cout << "]" << endl;
    
    return 0;
}

// Alternative version with integer output (more typical for competitive programming)
/*
vector<vector<pair<string, int>>> dailySummaryInt(const vector<pair<string, int>>& orders) {
    unordered_map<string, int> customerTotals;
    
    for (const auto& order : orders) {
        customerTotals[order.first] += order.second;
    }
    
    vector<pair<string, int>> result;
    result.reserve(customerTotals.size());
    
    for (const auto& customer : customerTotals) {
        result.emplace_back(customer.first, customer.second);
    }
    
    sort(result.begin(), result.end());
    
    return result;
}
*/