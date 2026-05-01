#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// ================= ENUM =================
enum class Difficulty { Easy, Hard };

// ================= BOARD =================
class Board {
private:
    vector<vector<char>> grid;
    const int size;

public:
    // Constructor
    Board(int size = 3) : size(size) {
        grid = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    // Display board
    void display() const {
        cout << "\n   1   2   3\n";
        for (int i = 0; i < size; i++) {
            cout << i + 1 << " ";
            for (int j = 0; j < size; j++) {
                cout << " " << grid[i][j] << " ";
                if (j < size - 1) cout << "|";
            }
            cout << "\n";
            if (i < size - 1) cout << "  ---+---+---\n";
        }
        cout << "\n";
    }

    // Check move validity
    bool isValidMove(int r, int c) const {
        return r >= 0 && r < size && c >= 0 && c < size && grid[r][c] == ' ';
    }

    // Place move
    bool makeMove(int r, int c, char s) {
        if (!isValidMove(r, c)) return false;
        grid[r][c] = s;
        return true;
    }

    // Check win condition
    bool checkWin(char s) const {
        // Rows
        for (int i = 0;

