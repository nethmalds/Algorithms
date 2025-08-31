#include <iostream>
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>

class InventoryTracker {
private:
    std::unordered_map<std::string, int> inventory;
    std::vector<std::string> insertionOrder; // Track order of first appearance
    
public:
    // Process a single transaction
    void processTransaction(const std::string& serialNumber, const std::string& action) {
        // If this is the first time seeing this serial number, record its order
        if (inventory.find(serialNumber) == inventory.end()) {
            insertionOrder.push_back(serialNumber);
            inventory[serialNumber] = 0;
        }
        
        if (action == "STOCK_IN") {
            inventory[serialNumber]++;
        } else if (action == "STOCK_OUT") {
            inventory[serialNumber]--;
        }
    }
    
    // Generate JSON output string maintaining input order
    std::string generateJSON() const {
        std::ostringstream json;
        json << "{\n";
        
        bool first = true;
        for (const std::string& serialNumber : insertionOrder) {
            if (!first) {
                json << ",\n";
            }
            json << "  \"" << serialNumber << "\": " << inventory.at(serialNumber);
            first = false;
        }
        
        json << "\n}";
        return json.str();
    }
    
    // Clear inventory data
    void clear() {
        inventory.clear();
        insertionOrder.clear();
    }
};

// Main function to solve the inventory tracking problem
std::string inventoryTracker() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    InventoryTracker tracker;
    
    // Process all transactions
    for (int i = 0; i < n; i++) {
        std::string serialNumber, action;
        std::cin >> serialNumber >> action;
        tracker.processTransaction(serialNumber, action);
    }
    
    return tracker.generateJSON();
}

int main() {
    std::string result = inventoryTracker();
    std::cout << result << std::endl;
    return 0;
}

// Alternative implementation with even better performance for very large datasets
class OptimizedInventoryTracker {
private:
    std::unordered_map<std::string, int> inventory;
    std::vector<std::string> insertionOrder; // Track order of first appearance
    
public:
    // Reserve space for better performance with known size
    void reserve(size_t expectedSize) {
        inventory.reserve(expectedSize);
        insertionOrder.reserve(expectedSize);
    }
    
    // Process transaction with move semantics for better performance
    void processTransaction(std::string&& serialNumber, const std::string& action) {
        // If this is the first time seeing this serial number, record its order
        if (inventory.find(serialNumber) == inventory.end()) {
            insertionOrder.push_back(serialNumber);
            inventory[std::move(serialNumber)] = 0;
        }
        
        if (action == "STOCK_IN") {
            ++inventory[serialNumber];
        } else {
            --inventory[serialNumber];
        }
    }
    
    // Generate JSON with pre-allocated string buffer maintaining input order
    std::string generateJSON() const {
        std::string json;
        json.reserve(insertionOrder.size() * 50); // Rough estimate for buffer size
        
        json += "{\n";
        bool first = true;
        for (const std::string& serialNumber : insertionOrder) {
            if (!first) {
                json += ",\n";
            }
            json += "  \"" + serialNumber + "\": " + std::to_string(inventory.at(serialNumber));
            first = false;
        }
        json += "\n}";
        
        return json;
    }
};

// High-performance version for competitive programming (maintains input order)
std::string fastInventoryTracker() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    
    int n;
    std::cin >> n;
    
    std::unordered_map<std::string, int> inv;
    std::vector<std::string> order;
    
    inv.reserve(n / 10); // Reasonable estimate for unique serials
    order.reserve(n / 10);
    
    for (int i = 0; i < n; ++i) {
        std::string serial, action;
        std::cin >> serial >> action;
        
        // If first time seeing this serial, record order
        if (inv.find(serial) == inv.end()) {
            order.push_back(serial);
            inv[serial] = 0;
        }
        
        // Direct increment/decrement based on action
        inv[serial] += (action[6] == 'I') ? 1 : -1; // Check 7th char: 'I' for IN, 'O' for OUT
    }
    
    // Build JSON string efficiently maintaining order
    std::string result = "{\n";
    bool first = true;
    
    for (const std::string& serial : order) {
        if (!first) result += ",\n";
        result += "  \"" + serial + "\": " + std::to_string(inv[serial]);
        first = false;
    }
    
    result += "\n}";
    return result;
}

/*
Performance Optimizations Implemented (with Input Order Preservation):

1. **Fast I/O**: 
   - std::ios_base::sync_with_stdio(false)
   - std::cin.tie(nullptr)

2. **Memory Efficiency**:
   - unordered_map for O(1) average access time
   - vector to track insertion order of unique serials
   - Reserve space when possible to avoid rehashing
   - Move semantics to avoid unnecessary string copies

3. **String Processing**:
   - Pre-allocate JSON string buffer
   - Use ostringstream for clean JSON formatting
   - Efficient character checking for action type

4. **Algorithm Efficiency**:
   - Single pass through transactions: O(n)
   - Hash map operations: O(1) average
   - Order preservation: O(1) per unique serial
   - Overall time complexity: O(n)
   - Space complexity: O(k) where k is unique serials

5. **Order Preservation**:
   - Track first appearance of each serial number
   - Use vector to maintain insertion order
   - Output follows input order of first appearance

Memory Usage (with order preservation):
- Each entry in hash map: ~40-80 bytes (key + value + overhead)
- Order vector: ~8 bytes per unique serial (pointer)
- For 1M transactions with 100K unique serials: ~5-10 MB
- JSON string: ~10-20 bytes per entry
- Total memory: < 25 MB for worst case

Time Complexity Analysis:
- Input reading: O(n)
- Hash map operations: O(n) average, O(n²) worst case
- Order tracking: O(k) where k is unique serials
- JSON generation: O(k) where k is unique serials
- Overall: O(n) average case

Key Features:
- Maintains input order of first serial number appearance
- Compatible with C++11 and later versions
- Fast I/O for competitive programming
- Memory-efficient design
- Handles negative stock counts correctly

Example with Order Preservation:
Input order: X-123, Y-456, X-123, Y-456, Z-789
Output order: X-123, Y-456, Z-789 (maintains first appearance order)
*/