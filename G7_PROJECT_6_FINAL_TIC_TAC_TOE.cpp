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
        for (int i = 0; i < size; i++) {
            if (grid[i][0] == s && grid[i][1] == s && grid[i][2] == s) return true;
        }
        // Columns
        for (int j = 0; j < size; j++) {
            if (grid[0][j] == s && grid[1][j] == s && grid[2][j] == s) return true;
        }
        // Diagonals
        if (grid[0][0] == s && grid[1][1] == s && grid[2][2] == s) return true;
        if (grid[0][2] == s && grid[1][1] == s && grid[2][0] == s) return true;

        return false;
    }

    // Check draw
    bool isFull() const {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                if (grid[i][j] == ' ') return false;
            }
        }
        return true;
    }

    // Get cell
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

    // Get size
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

    virtual void getMove(const Board& board, int& row, int& col) = 0;

    string getName() const { return name; }
    char getSymbol() const { return symbol; }
    void setName(const string& name) { this->name = name; }

    virtual ~Player() {}
};

// ================= HUMAN PLAYER =================
class HumanPlayer : public Player {
public:
    HumanPlayer(const string& name, char symbol) : Player(name, symbol) {}

    void getMove(const Board& board, int& r, int& c) override {
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
        : Player(name, symbol), difficulty(difficulty) {}

    void setDifficulty(Difficulty d) { difficulty = d; }

    int evaluateBoard(const Board& board) const {
        char ai = symbol;
        char opp = (symbol == 'X') ? 'O' : 'X';

        if (board.checkWin(ai)) return 10;
        if (board.checkWin(opp)) return -10;
        if (board.isFull()) return 0;

        int bestScore = -1000;
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.isValidMove(i, j)) {
                    Board temp = board;
                    temp.makeMove(i, j, ai);
                    int score = -evaluateBoard(temp);
                    bestScore = max(bestScore, score);
                }
            }
        }
        return bestScore;
    }

    void getMove(const Board& board, int& r, int& c) override {
        if (difficulty == Difficulty::Easy) {
            getRandomMove(board, r, c);
        } else {
            getBestMove(board, r, c);
            if (r == -1 || c == -1) getRandomMove(board, r, c);
        }
    }

    void getRandomMove(const Board& board, int& r, int& c) const {
        srand(time(0));
        do {
            r = rand() % board.getSize();
            c = rand() % board.getSize();
        } while (!board.isValidMove(r, c));
    }

    void getBestMove(const Board& board, int& r, int& c) const {
        int bestScore = -1000;
        r = c = -1;
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {
                if (board.isValidMove(i, j)) {
                    Board temp = board;
                    temp.makeMove(i, j, symbol);
                    int score = evaluateBoard(temp);
                    if (score > bestScore) {
                        bestScore = score;
                        r = i; c = j;
                    }
                }
            }
        }
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
    Game() : board(3), p1(nullptr), p2(nullptr), current(nullptr) {}

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
        string n1, n2;
        cout << "Enter Player 1 name: "; cin >> n1;
        cout << "Enter Player 2 name: "; cin >> n2;
        p1 = new HumanPlayer(n1, 'X');
        p2 = new HumanPlayer(n2, 'O');
        current = p1;
    }

    void setupPvC(Difficulty d) {
        string n1;
        cout << "Enter Player name: "; cin >> n1;
        p1 = new HumanPlayer(n1, 'X');
        p2 = new AIPlayer("Computer", 'O', d);
        current = p1;
    }

    void switchPlayer() {
        current = (current == p1) ? p2 : p1;
    }

    void handleHumanMove(Player* player) {
        int r, c;
        player->getMove(board, r, c);
        board.makeMove(r, c, player->getSymbol());
    }

    void handleAIMove(Player* player) {
        int r, c;
        player->getMove(board, r, c);
        board.makeMove(r, c, player->getSymbol());
        cout << player->getName() << " (" << player->getSymbol()
             << ") plays at (" << r+1 << "," << c+1 << ")\n";
    }

    bool checkGameEnd() const {
        return board.checkWin('X') || board.checkWin('O') || board.isFull();
    }

    void displayResult() const {
        if (board.check
