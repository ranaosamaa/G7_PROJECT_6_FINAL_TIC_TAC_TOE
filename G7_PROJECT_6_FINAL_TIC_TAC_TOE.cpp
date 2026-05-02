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

        for (int i = 0; i < size; i++) {
            bool win = true;
            for (int j = 0; j < size; j++) {
                if (grid[i][j] != s) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    
        for (int j = 0; j < size; j++) {
            bool win = true;
            for (int i = 0; i < size; i++) {
                if (grid[i][j] != s) {
                    win = false;
                    break;
                }
            }
            if (win) return true;
        }
    
        bool win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][i] != s) {
                win = false;
                break;
            }
        }
        if (win) return true;
    
        win = true;
        for (int i = 0; i < size; i++) {
            if (grid[i][size - 1 - i] != s) {
                win = false;
                break;
            }
        }
        if (win) return true;
    
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
        while (true) {
        cout << name << " (" << symbol << "), enter row and column (1-3): ";
        cin >> r >> c;

        // Convert to 0-based
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
    void setDifficulty(Difficulty d) {
        difficulty = d;
    }

    int evaluateBoard(const Board& board) const {
        char ai = symbol;
        char opp = (symbol == 'X') ? 'O' : 'X';

        // Base cases: terminal states
        if (board.checkWin(ai)) return 10;
        if (board.checkWin(opp)) return -10;
        if (board.isFull()) return 0;

        int bestScore = -1000;

        // Try all possible moves
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = 0; j < board.getSize(); j++) {

                if (board.isValidMove(i, j)) {
                    Board temp = board;
                    temp.makeMove(i, j, ai);

                    int score = -evaluateBoard(temp);

                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }

        return bestScore;
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
        if (difficulty == Difficulty::Easy) {
        // Easy mode: random valid move
        getRandomMove(board, r, c);
    } else {
        // Hard mode: try best move using evaluation
        getBestMove(board, r, c);

        // Safety fallback: if no best move found, pick random
        if (r == -1 || c == -1) {
            getRandomMove(board, r, c);
        }
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
        cout << "Select Game Mode :";
    }

    void setupPvP() {
        string name1, name2;
        cout << "Enter name for Player 1 (X): ";
        cin >> name1;
        cout << "Enter name for Player 2 (O): ";
        cin >> name2;

        p1 = new HumanPlayer(name1, 'X');
        p2 = new HumanPlayer(name2, 'O');
        current = p1;
    }

    void setupPvC(Difficulty d) {
        string name;
        cout << "Enter your name: ";
        cin >> name;

        p1 = new HumanPlayer(name, 'X');
        p2 = new AIPlayer("Computer", 'O', d);
        current = p1;
    }

    void switchPlayer() {
        current = (current == p1) ? p2 : p1;
    }

    void handleHumanMove(Player* player) {
        /*
        - Get move from player
        - Validate and apply move on board
        */
    }
    void handleAIMove(Player* player) {
        /*
        - Get move from player
        - Validate and apply move on board
        */
        int r, c;
        player->getMove(board, r, c);  // Ask AI for move
        board.makeMove(r, c, player->getSymbol());  // Apply move
        cout << player->getName() << " (" << player->getSymbol()
        << ") plays at (" << r+1 << "," << c+1 << ")\n";
    }

    bool checkGameEnd() const {
        return board.checkWin('X') || board.checkWin('O') || board.isFull();
    }

    void displayResult() const {
        if (board.checkWin('X'))
            cout << p1->getName() << " (X) wins!\n";
        else if (board.checkWin('O'))
            cout << p2->getName() << " (O) wins!\n";
        else
            cout << "Draw!\n";
    }

    void reset() {
        board.reset();
    }

    void start() {
        /*
        MAIN GAME LOOP:
        do:
        - Show menu
        - Setup game mode
        - Loop:
            - display board
            - player move
            - check win/draw
            - switch player
        - Ask replay
        - reset game if yes
        */
        bool exit = false;
    
        while (!exit) {
            reset();
    
            showMenu();
            int n;
            cin >> n;
    
            if (n == 1)
                setupPvP();
            else if (n == 2)
                setupPvC(Difficulty::Easy);
            else if (n == 3)
                setupPvC(Difficulty::Hard);
            else
                return;
    
            while (!checkGameEnd()) {
                board.display();
                if (current->getName() == "Computer")
                    handleAIMove(current);
                else
                    handleHumanMove(current);
                if (!checkGameEnd())
                    switchPlayer();
            }
            board.display();
            displayResult();
            cout << "Wanna Replay? (Y/N): ";
            char c;
            cin >> c;
            if (c != 'Y' && c != 'y')
                exit = true;
        }
}
};

int main() {
    Game game;
    game.start();
    return 0;
}
