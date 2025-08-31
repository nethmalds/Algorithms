#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <cassert>

using namespace std;

class TestCaseGenerator {
private:
    mt19937 rng;
    
public:
    TestCaseGenerator() : rng(random_device{}()) {}
    
    // Generate a basic valid test case
    void generateBasicTest(int R, int C, const string& filename) {
        ofstream file(filename);
        file << R << " " << C << "\n";
        
        vector<string> grid(R, string(C, '.'));
        
        // Place start and goal randomly
        int startR = rng() % R;
        int startC = rng() % C;
        int goalR, goalC;
        
        do {
            goalR = rng() % R;
            goalC = rng() % C;
        } while (goalR == startR && goalC == startC);
        
        grid[startR][startC] = 'S';
        grid[goalR][goalC] = 'G';
        
        // Add some random obstacles
        int obstacles = (R * C) / 5; // 20% obstacles
        for (int i = 0; i < obstacles; i++) {
            int r = rng() % R;
            int c = rng() % C;
            if (grid[r][c] == '.') {
                grid[r][c] = '#';
            }
        }
        
        for (const auto& row : grid) {
            file << row << "\n";
        }
        
        file.close();
        cout << "Generated basic test case: " << filename << "\n";
    }
    
    // Generate test with guaranteed path
    void generatePathTest(int R, int C, const string& filename) {
        ofstream file(filename);
        file << R << " " << C << "\n";
        
        vector<string> grid(R, string(C, '#'));
        
        // Create a clear path from top-left to bottom-right
        int startR = 0, startC = 0;
        int goalR = R - 1, goalC = C - 1;
        
        // Clear a simple path
        for (int i = 0; i < R; i++) {
            grid[i][0] = '.'; // Clear leftmost column
        }
        for (int j = 0; j < C; j++) {
            grid[R-1][j] = '.'; // Clear bottom row
        }
        
        grid[startR][startC] = 'S';
        grid[goalR][goalC] = 'G';
        
        for (const auto& row : grid) {
            file << row << "\n";
        }
        
        file.close();
        cout << "Generated guaranteed path test: " << filename << "\n";
    }
    
    // Generate test with no path (isolated goal)
    void generateNoPathTest(int R, int C, const string& filename) {
        ofstream file(filename);
        file << R << " " << C << "\n";
        
        vector<string> grid(R, string(C, '.'));
        
        // Place start
        grid[0][0] = 'S';
        
        // Place goal and surround it with walls
        int goalR = R - 1;
        int goalC = C - 1;
        grid[goalR][goalC] = 'G';
        
        // Surround goal with walls
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                int nr = goalR + dr;
                int nc = goalC + dc;
                if (nr >= 0 && nr < R && nc >= 0 && nc < C && 
                    !(nr == goalR && nc == goalC)) {
                    grid[nr][nc] = '#';
                }
            }
        }
        
        for (const auto& row : grid) {
            file << row << "\n";
        }
        
        file.close();
        cout << "Generated no path test: " << filename << "\n";
    }
    
    // Generate edge case tests
    void generateEdgeCases() {
        // Single cell with start and goal at same position
        {
            ofstream file("test_single_cell.txt");
            file << "1 1\n";
            file << "S\n"; // No goal - should return -1
            file.close();
        }
        
        // Minimum size with path
        {
            ofstream file("test_min_path.txt");
            file << "1 2\n";
            file << "SG\n";
            file.close();
        }
        
        // Large maze
        {
            ofstream file("test_large_maze.txt");
            int R = 50, C = 50;
            file << R << " " << C << "\n";
            
            vector<string> grid(R, string(C, '.'));
            
            // Create a maze-like structure
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if ((i + j) % 3 == 0 && !(i == 0 && j == 0) && !(i == R-1 && j == C-1)) {
                        grid[i][j] = '#';
                    }
                }
            }
            
            grid[0][0] = 'S';
            grid[R-1][C-1] = 'G';
            
            for (const auto& row : grid) {
                file << row << "\n";
            }
            file.close();
        }
        
        // Missing start
        {
            ofstream file("test_no_start.txt");
            file << "3 3\n";
            file << "...\n";
            file << ".G.\n";
            file << "...\n";
            file.close();
        }
        
        // Missing goal
        {
            ofstream file("test_no_goal.txt");
            file << "3 3\n";
            file << "...\n";
            file << ".S.\n";
            file << "...\n";
            file.close();
        }
        
        // All walls except start and goal
        {
            ofstream file("test_all_walls.txt");
            file << "3 3\n";
            file << "S##\n";
            file << "###\n";
            file << "##G\n";
            file.close();
        }
        
        cout << "Generated edge case tests\n";
    }
    
    // Generate the sample test case from your example
    void generateSampleTest() {
        ofstream file("test_sample.txt");
        file << "4 5\n";
        file << "S.#.G\n";
        file << "#....\n";
        file << ".#..#\n";
        file << "..#..\n";
        file.close();
        cout << "Generated sample test case\n";
    }
    
    // Generate stress tests
    void generateStressTests() {
        // Maximum size grid with complex paths
        {
            ofstream file("test_stress_complex.txt");
            int R = 50, C = 50;
            file << R << " " << C << "\n";
            
            vector<string> grid(R, string(C, '.'));
            
            // Create a spiral pattern of walls
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if ((i + j) % 7 == 0 || (i - j) % 5 == 0) {
                        grid[i][j] = '#';
                    }
                }
            }
            
            // Ensure start and goal are clear
            grid[0][0] = 'S';
            grid[R-1][C-1] = 'G';
            
            // Clear a guaranteed path along edges
            for (int i = 0; i < R; i++) {
                if (grid[i][0] == '#') grid[i][0] = '.';
            }
            for (int j = 0; j < C; j++) {
                if (grid[R-1][j] == '#') grid[R-1][j] = '.';
            }
            
            for (const auto& row : grid) {
                file << row << "\n";
            }
            file.close();
        }
        
        // Dense obstacle field
        {
            ofstream file("test_stress_dense.txt");
            int R = 40, C = 40;
            file << R << " " << C << "\n";
            
            vector<string> grid(R, string(C, '#'));
            
            // Create random clear spaces
            uniform_int_distribution<int> dist(0, 9);
            for (int i = 0; i < R; i++) {
                for (int j = 0; j < C; j++) {
                    if (dist(rng) < 3) { // 30% chance of clear space
                        grid[i][j] = '.';
                    }
                }
            }
            
            grid[0][0] = 'S';
            grid[R-1][C-1] = 'G';
            
            for (const auto& row : grid) {
                file << row << "\n";
            }
            file.close();
        }
        
        cout << "Generated stress tests\n";
    }
    
    // Generate invalid input tests
    void generateInvalidTests() {
        // Invalid dimensions
        {
            ofstream file("test_invalid_dims.txt");
            file << "0 5\n";
            file.close();
        }
        
        {
            ofstream file("test_negative_dims.txt");
            file << "-1 5\n";
            file.close();
        }
        
        {
            ofstream file("test_too_large.txt");
            file << "100 100\n";
            file.close();
        }
        
        // Inconsistent row lengths
        {
            ofstream file("test_inconsistent_rows.txt");
            file << "3 4\n";
            file << "S..G\n";
            file << "#..\n";    // Too short
            file << ".....\n";  // Too long
            file.close();
        }
        
        cout << "Generated invalid input tests\n";
    }
};

// Test runner to validate your solution
class TestRunner {
public:
    void runAllTests() {
        vector<pair<string, int>> testCases = {
            {"test_sample.txt", 6},        // Expected: 6
            {"test_min_path.txt", 1},      // Expected: 1
            {"test_single_cell.txt", -1},  // Expected: -1 (no goal)
            {"test_no_start.txt", -1},     // Expected: -1
            {"test_no_goal.txt", -1},      // Expected: -1
            {"test_all_walls.txt", -1},    // Expected: -1 (no path)
        };
        
        cout << "\n=== Running Test Cases ===\n";
        for (const auto& [filename, expected] : testCases) {
            cout << "Testing " << filename << " (expected: " << expected << ")\n";
            // Here you would run your actual solution and compare results
            // This is a framework - you'd integrate with your actual code
        }
    }
};

int main() {
    TestCaseGenerator generator;
    
    cout << "Generating test cases for BFS pathfinding...\n\n";
    
    // Generate various types of test cases
    generator.generateSampleTest();
    generator.generateBasicTest(5, 5, "test_basic_5x5.txt");
    generator.generateBasicTest(10, 8, "test_basic_10x8.txt");
    generator.generatePathTest(6, 6, "test_guaranteed_path.txt");
    generator.generateNoPathTest(7, 7, "test_no_path.txt");
    generator.generateEdgeCases();
    generator.generateStressTests();
    generator.generateInvalidTests();
    
    cout << "\nAll test cases generated successfully!\n";
    cout << "You can now run these test files against your BFS solution.\n";
    
    // Optional: Run tests if you integrate with your solution
    TestRunner runner;
    runner.runAllTests();
    
    return 0;
}