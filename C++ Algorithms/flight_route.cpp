#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

struct RouteRevenue {
    string route;
    long long revenue;
    
    RouteRevenue(const string& r, long long rev) : route(r), revenue(rev) {}
};

// Custom comparator for sorting routes
bool compareRoutes(const RouteRevenue& a, const RouteRevenue& b) {
    if (a.revenue != b.revenue) {
        return a.revenue > b.revenue; // Higher revenue first
    }
    return a.route < b.route; // Lexicographical order for ties
}

// Function to parse customer name (handles quoted names)
string parseCustomerName(const string& line, size_t& pos) {
    string name;
    
    // Skip whitespace
    while (pos < line.length() && isspace(line[pos])) pos++;
    
    if (pos < line.length() && line[pos] == '"') {
        // Quoted name
        pos++; // Skip opening quote
        while (pos < line.length() && line[pos] != '"') {
            name += line[pos];
            pos++;
        }
        if (pos < line.length() && line[pos] == '"') {
            pos++; // Skip closing quote
        }
    } else {
        // Unquoted name (single word)
        while (pos < line.length() && !isspace(line[pos])) {
            name += line[pos];
            pos++;
        }
    }
    
    return name;
}

// Function to parse the next token
string parseToken(const string& line, size_t& pos) {
    string token;
    
    // Skip whitespace
    while (pos < line.length() && isspace(line[pos])) pos++;
    
    // Extract token
    while (pos < line.length() && !isspace(line[pos])) {
        token += line[pos];
        pos++;
    }
    
    return token;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    cin.ignore(); // Ignore the newline after the number
    
    unordered_map<string, long long> routeRevenues;
    
    for (int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        
        size_t pos = 0;
        
        // Parse BookingID
        string bookingId = parseToken(line, pos);
        
        // Parse Customer Name (may be quoted)
        string customerName = parseCustomerName(line, pos);
        
        // Parse Origin
        string origin = parseToken(line, pos);
        
        // Parse Destination
        string destination = parseToken(line, pos);
        
        // Parse Ticket Price
        string priceStr = parseToken(line, pos);
        int ticketPrice = stoi(priceStr);
        
        // Create route string
        string route = origin + "->" + destination;
        
        // Add to total revenue for this route
        routeRevenues[route] += ticketPrice;
    }
    
    // Convert map to vector for sorting
    vector<RouteRevenue> routes;
    routes.reserve(routeRevenues.size());
    
    for (const auto& pair : routeRevenues) {
        routes.emplace_back(pair.first, pair.second);
    }
    
    // Sort routes by revenue (descending) and then lexicographically
    sort(routes.begin(), routes.end(), compareRoutes);
    
    // Output results
    for (const RouteRevenue& route : routes) {
        cout << route.route << " " << route.revenue << "\n";
    }
    
    return 0;
}