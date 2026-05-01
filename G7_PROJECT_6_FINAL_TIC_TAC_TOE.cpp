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
        /*
        - Check rows
        - Check columns
        - Check diagonals
        */
    }

    // Check draw
    bool isFull() const {
        /*
        - Return true if no empty cells remain
        */

        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == ' ') return false;
            }
        }
        return true;
    }

    // Get cell (IMPLEMENTED)
    char getCell(int r, int c) const {
        if (r >= 0 && r < size && c >= 0 && c < size) return grid[r][c];
        return ' ';
    }

    // Reset board
    void reset() {
        for (int r = 0; r < size; r++) {
            for (int c = 0; c < size; c++) {
                grid[r][c] = ' ';
            }
        }
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
    string getName() const { return name; }

    // Getter (IMPLEMENTED)
    char getSymbol() const { return symbol; }

    // Setter (IMPLEMENTED)
    void setName(const string& name) { this->name = name; }

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

        while (true) {
            cout << name << " (" << symbol << "), enter row and column (1-3): ";
            cin >> r >> c;
            r--; c--;

            if (cin.fail() || !board.isValidMove(r, c)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid move. Try again.\n";
            } else {
                break;
            }
        }
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
    void setDifficulty(Difficulty d) { difficulty = d; }

    int evaluateBoard(const Board& board) const { return 0; } // left for later

    void getMove(const Board& board, int& r, int& c) override {
        /*
        EASY:
        - Choose random valid move

        HARD:
        - Try winning move
        - Try blocking opponent win
        - Otherwise pick random move
        */

        if (difficulty == Difficulty::Easy) {
            getRandomMove(board, r, c);
        } else {
            getBestMove(board, r, c);
            if (r == -1 || c == -1) getRandomMove(board, r, c);
        }
    }

    void getRandomMove(const Board& board, int& r, int& c) const {
        /*
        - Generate random row/col
        - Repeat until valid move found
        */

        srand(time(0));
        do {
            r = rand() % board.getSize();
            c = rand() % board.getSize();
        } while (!board.isValidMove(r, c));
    }

    void getBestMove(const Board& board, int& r, int& c) const {
        // goes through every cell on the board and checks if the move is valid.
        // For each valid move, it:
        //    creates a copy of the board
        //    applies the move on the copy
        //    evaluates the result using evaluateBoard()
        //
        // It keeps track of the move with the highest score,
        // and in the end, (row, col) will contain the best possible move.
        //
        // Important: the real board is never changed here, only copies are used.
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
    Game() : board(3) { p1 = p2 = current = nullptr; }

    void showMenu() { /* left for later */ }
    void setupPvP() { /* left for later */ }
    void setupPvC(Difficulty d) { /* left for later */ }
    void switchPlayer() { /* left for later */ }
    void handleHumanMove(Player* player) { /* left for later */ }

    void handleAIMove(Player* player) {
        /*
        - Get move from player
        - Validate and apply move on board
        */

        int r, c;
        player->getMove(board, r, c);
        board.makeMove(r, c, player->getSymbol());
        cout << player->getName() << " (" << player->getSymbol()
             << ") plays at (" << r+1 << "," << c+1 << ")\n";
    }

    bool checkGameEnd() const { return false; }
    void displayResult() const { /* left for later */ }
    void reset() { board.reset(); }
    void start() { /* left for later */ }
};

// ================= MAIN =================
int main() {
    Game game;
    game.start();
    return 0;
}
