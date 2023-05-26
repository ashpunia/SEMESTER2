// #include <iostream>
// #include <vector>
// #include <string>
// #include <algorithm>

// using namespace std;

// // Function to generate all possible word search grids
// void generateWordSearchGrids(vector<string>& words, int x, int y) {
//     // Calculate the maximum possible length of a word in the grid
//     int maxLength = max(x, y);

//     // Loop through all possible lengths of the words in the grid
//     for (int length = 1; length <= maxLength; length++) {
//         // Loop through all possible directions for the words in the grid
//         for (int dx = -1; dx <= 1; dx++) {
//             for (int dy = -1; dy <= 1; dy++) {
//                 // Skip the (0, 0) direction as it is not a valid direction
//                 if (dx == 0 && dy == 0) {
//                     continue;
//                 }

//                 // Loop through all possible starting positions for the words in the grid
//                 for (int row = 0; row < y; row++) {
//                     for (int col = 0; col < x; col++) {
//                         // Calculate the ending position of the word
//                         int endRow = row + (length - 1) * dy;
//                         int endCol = col + (length - 1) * dx;

//                         // Skip the word if it goes out of the bounds of the grid
//                         if (endRow < 0 || endRow >= y || endCol < 0 || endCol >= x) {
//                             continue;
//                         }

//                         // Create a new word search grid
//                         vector<vector<char>> grid(y, vector<char>(x, '.'));

//                         // Add the words to the grid
//                         for (string word : words) {
//                             // Loop through all possible orientations of the word in the grid
//                             for (int i = 0; i < length; i++) {
//                                 int rowi = row + i * dy;
//                                 int coli = col + i * dx;

//                                 // Add the character to the grid
//                                 grid[rowi][coli] = word[i];
//                             }
//                         }

//                         // Print the word search grid
//                         for (int i = 0; i < y; i++) {
//                             for (int j = 0; j < x; j++) {
//                                 cout << grid[i][j] << " ";
//                             }
//                             cout << endl;
//                         }
//                         cout << endl;
//                     }
//                 }
//             }
//         }
//     }
// }

// int main() {
//     // Input the list of words
//     vector<string> words = {"apple", "banana", "cherry", "grape"};

//     // Input the dimensions of the word search grid
//     int x = 5;
//     int y = 5;

//     // Generate all possible word search grids
//     generateWordSearchGrids(words, x, y);

//     return 0;
// }

#include <iostream>
#include <string>
#include <vector>

using namespace std;

void generate_word_search_grids(vector<string> words, int x, int y, vector<vector<char>>& grid, int word_index) {
    if (word_index == words.size()) { // Base case: All words have been placed in the grid
        for (int i = 0; i < x; i++) {
            for (int j = 0; j < y; j++) {
                cout << grid[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
        return;
    }

    string word = words[word_index];

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            // Check if the current position in the grid can accommodate the current word horizontally
            if (y - j >= word.size()) {
                bool valid = true;
                for (int k = 0; k < word.size(); k++) {
                    if (grid[i][j + k] != ' ' && grid[i][j + k] != word[k]) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    // Place the word horizontally in the grid
                    for (int k = 0; k < word.size(); k++) {
                        grid[i][j + k] = word[k];
                    }

                    // Recurse to place the next word in the grid
                    generate_word_search_grids(words, x, y, grid, word_index + 1);

                    // Backtrack to try a different position for the current word
                    for (int k = 0; k < word.size(); k++) {
                        grid[i][j + k] = ' ';
                    }
                }
            }

            // Check if the current position in the grid can accommodate the current word vertically
            if (x - i >= word.size()) {
                bool valid = true;
                for (int k = 0; k < word.size(); k++) {
                    if (grid[i + k][j] != ' ' && grid[i + k][j] != word[k]) {
                        valid = false;
                        break;
                    }
                }
                if (valid) {
                    // Place the word vertically in the grid
                    for (int k = 0; k < word.size(); k++) {
                        grid[i + k][j] = word[k];
                    }

                    // Recurse to place the next word in the grid
                    generate_word_search_grids(words, x, y, grid, word_index + 1);

                    // Backtrack to try a different position for the current word
                    for (int k = 0; k < word.size(); k++) {
                        grid[i + k][j] = ' ';
                    }
                }
            }
        }
    }
}

int main() {
    vector<string> words = {"Ash", "Mike", "Vincent", "Tacobell"};
    int x = 10;
    int y = 10;

    vector<vector<char>> grid(x, vector<char>(y, ' ')); // Initialize the grid with empty spaces

    generate_word_search_grids(words, x, y, grid, 0);

    return 0;
}