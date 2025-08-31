#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <sstream>

struct Task {
    std::string name;
    int priority;
    int order; // For FIFO tie-breaking
    
    Task(const std::string& n, int p, int o) : name(n), priority(p), order(o) {}
    
    // Custom comparator for max-heap with FIFO tie-breaking
    // Higher priority first, if same priority then earlier order (lower order value)
    bool operator<(const Task& other) const {
        if (priority != other.priority) {
            return priority < other.priority; // Max-heap for priority
        }
        return order > other.order; // Min-heap for order (FIFO)
    }
};

std::vector<std::string> taskManager(const std::vector<std::vector<std::string>>& operations) {
    std::priority_queue<Task> pq;
    std::vector<std::string> result;
    int orderCounter = 0; // To maintain insertion order for FIFO tie-breaking
    
    for (const auto& op : operations) {
        if (op[0] == "ADD") {
            std::string taskName = op[1];
            int priority = std::stoi(op[2]);
            pq.push(Task(taskName, priority, orderCounter++));
        } else if (op[0] == "RETRIEVE") {
            if (!pq.empty()) {
                Task highestPriorityTask = pq.top();
                pq.pop();
                result.push_back(highestPriorityTask.name);
            }
        }
    }
    
    return result;
}

// Helper function to parse input and test the solution
std::vector<std::vector<std::string>> parseInput() {
    int n;
    std::cin >> n;
    std::cin.ignore(); // Ignore the newline after the number
    
    std::vector<std::vector<std::string>> operations;
    
    for (int i = 0; i < n; i++) {
        std::string line;
        std::getline(std::cin, line);
        
        std::vector<std::string> operation;
        std::stringstream ss(line);
        std::string token;
        
        while (ss >> token) {
            operation.push_back(token);
        }
        
        operations.push_back(operation);
    }
    
    return operations;
}

int main() {
    // Parse input
    std::vector<std::vector<std::string>> operations = parseInput();
    
    // Execute task manager
    std::vector<std::string> result = taskManager(operations);
    
    // Output results
    for (const std::string& taskName : result) {
        std::cout << taskName << std::endl;
    }
    
    return 0;
}

// Alternative implementation using manual heap for even better performance
class FastTaskManager {
private:
    struct Task {
        std::string name;
        int priority;
        int order;
        
        Task(const std::string& n, int p, int o) : name(n), priority(p), order(o) {}
    };
    
    std::vector<Task> heap;
    int orderCounter;
    
    void heapifyUp(int idx) {
        while (idx > 0) {
            int parent = (idx - 1) / 2;
            if (shouldSwap(idx, parent)) {
                std::swap(heap[idx], heap[parent]);
                idx = parent;
            } else {
                break;
            }
        }
    }
    
    void heapifyDown(int idx) {
        int size = heap.size();
        while (true) {
            int largest = idx;
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            
            if (left < size && shouldSwap(left, largest)) {
                largest = left;
            }
            if (right < size && shouldSwap(right, largest)) {
                largest = right;
            }
            
            if (largest != idx) {
                std::swap(heap[idx], heap[largest]);
                idx = largest;
            } else {
                break;
            }
        }
    }
    
    bool shouldSwap(int child, int parent) {
        // Child should be swapped with parent if:
        // 1. Child has higher priority, OR
        // 2. Same priority but child was added earlier (lower order)
        if (heap[child].priority != heap[parent].priority) {
            return heap[child].priority > heap[parent].priority;
        }
        return heap[child].order < heap[parent].order;
    }
    
public:
    FastTaskManager() : orderCounter(0) {}
    
    void addTask(const std::string& name, int priority) {
        heap.push_back(Task(name, priority, orderCounter++));
        heapifyUp(heap.size() - 1);
    }
    
    std::string retrieveTask() {
        if (heap.empty()) return "";
        
        std::string result = heap[0].name;
        heap[0] = heap.back();
        heap.pop_back();
        
        if (!heap.empty()) {
            heapifyDown(0);
        }
        
        return result;
    }
};