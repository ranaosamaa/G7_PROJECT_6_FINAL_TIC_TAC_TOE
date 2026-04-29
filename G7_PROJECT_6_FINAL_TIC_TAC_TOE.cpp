#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>
#include <ctime>
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

    // Display board (IMPLEMENTED)
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
        /*
        - Check bounds (0 <= r,c < size)
        - Check if cell is empty
        */
        return false;
    }

    // Place move
    bool makeMove(int r, int c, char s) {
        /*
        - Use isValidMove
        - If valid: place symbol and return true
        - Else return false
        */
        return false;
    }

    // Check win condition
    bool checkWin(char s) const {
        /*
        - Check rows
        - Check columns
        - Check diagonals
        */
        return false;
    }

    // Check draw
    bool isFull() const {
        /*
        - Return true if no empty cells remain
        */
        return false;
    }

    // Get cell (IMPLEMENTED)
    char getCell(int r, int c) const {
        if (r < size && c < size) return grid[r][c];
        else return ' ';
    }

    // Reset board
    void reset() {
        /*
        - Set all cells to ' '
        */
    }

    // Get size (IMPLEMENTED)
    int getSize() const {
        return size;
    }
};

// ================= PLAYER =================
class Player {
protected:
    string name;
    char symbol;

public:
    Player(const string& name, char symbol) {
        this->name = name;
        this->symbol = symbol;
    }

    // Get move (NOW TAKES BOARD)
    virtual void getMove(const Board& board, int& row, int& col) = 0;

    // Getter (IMPLEMENTED)
    string getName() const {
        return name;
    }

    // Getter (IMPLEMENTED)
    char getSymbol() const {
        return symbol;
    }

    // Setter (IMPLEMENTED)
    void setName(const string& name) {
        this->name = name;
    }

    virtual ~Player() {}
};

// ================= HUMAN PLAYER =================
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getMove(const Board& board, int& r, int& c) override {
        /*
        - Ask user for row and column (1-3)
        - Convert to 0-based index
        - Validate input format
        - Ensure move is valid using board.isValidMove()
        - Repeat until valid input is given
        */
    }
};

// ================= AI PLAYER =================
class AIPlayer : public Player {
private:
    Difficulty difficulty;

public:
    AIPlayer(const string& name, char symbol, Difficulty difficulty)
        : Player(name, symbol) {
        this->difficulty = difficulty;
    }

    // Setter (IMPLEMENTED)
    void setDifficulty(Difficulty d) {
        difficulty = d;
    }

    void getMove(const Board& board, int& r, int& c) override {
        /*
        EASY:
        - Choose random valid move

        HARD:
        - Try winning move
        - Try blocking opponent win
        - Otherwise pick random move
        */
    }

    void getRandomMove(const Board& board, int& r, int& c) const {
        /*
        - Generate random row/col
        - Repeat until valid move found
        */
    }
};

// ================= GAME =================
class Game {
private:
    Board board;
    Player* p1;
    Player* p2;
    Player* current;

public:
    Game() : board(3) {
        p1 = p2 = current = nullptr;
    }

    void showMenu() {
        cout << "\nTIC-TAC-TOE GAME\n";
        cout << "================\n";
        cout << "1. Player VS Player\n";
        cout << "2. Player VS Computer (Easy)\n";
        cout << "3. Player VS Computer (Hard)\n";
        cout << "4. Exit\n";
        cout << "Select Game Mode: ";
    }

    void setupPvP() {
        /*
        - Ask names
        - Create 2 HumanPlayer objects
        - Assign X and O
        - Set current player
        */
    }

    void setupPvC(Difficulty d) {
        /*
        - Ask player name
        - Create Human + AI player
        - Assign symbols
        - Pass difficulty to AI
        */
    }

    void switchPlayer() {
        /*
        - Toggle between p1 and p2
        */
    }

    void handleMove(Player* player) {
        /*
        - Get move from player
        - Validate and apply move on board
        */
    }

    bool checkGameEnd() const {
        /*
        - Check win for X
        - Check win for O
        - Check draw (board full)
        */
        return false;
    }

    void displayResult() const {
        /*
        - Print winner name + symbol
        - OR print draw message
        */
    }

    void reset() {
        /*
        - Reset board
        */
    }

    void start() {
        /*
        MAIN GAME LOOP:
        - Show menu
        - Setup game mode
        - Loop:
            - display board
            - player move
            - check win/draw
            - switch player
        - Ask replay
        */
    }
};

// ================= MAIN =================
int main() {
    Game game;
    game.start();
    return 0;
}