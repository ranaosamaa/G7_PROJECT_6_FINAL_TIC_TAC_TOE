# Tic-Tac-Toe (C++ Console Game)

A modular, object-oriented Tic-Tac-Toe game implemented in C++. The project supports both human and AI gameplay with multiple difficulty levels and demonstrates clean class design, recursion (Minimax), and game loop management.

---

## Features

* **Multiple Game Modes**

  * Player vs Player
  * Player vs Computer (Easy)
  * Player vs Computer (Hard – Minimax AI)

* **AI System**

  * Easy mode: random moves
  * Hard mode: optimal play using Minimax algorithm

* **Object-Oriented Design**

  * Separate classes for Board, Player, AI, and Game
  * Polymorphism for handling human and AI players

* **Game Mechanics**

  * Input validation
  * Win and draw detection
  * Replay support

---

## Project Structure

```
.
├── main.cpp
├── Board class        // Grid management, validation, win/draw logic
├── Player class       // Abstract base class
├── HumanPlayer        // Handles user input
├── AIPlayer           // Implements random + minimax AI
└── Game class         // Controls game flow and menu
```

---

## How to Run

### 1. Compile

```bash
g++ -o tic_tac_toe main.cpp
```

### 2. Run

```bash
./tic_tac_toe
```

---

## Gameplay Instructions

* Select a game mode from the menu
* Enter moves using row and column numbers (1–3)
* Example input:

  ```
  1 3
  ```
* The game continues until:

  * A player wins
  * The board is full (draw)

---

## AI Implementation Details

The **Hard mode AI** uses the **Minimax algorithm**:

* Recursively evaluates all possible game states
* Assigns scores:

  * `+10` → AI win
  * `-10` → Opponent win
  * `0` → Draw
* Chooses the move with the best possible outcome

---

## Key Concepts Demonstrated

* Object-Oriented Programming (OOP)
* Inheritance and Polymorphism
* Recursion (Minimax)
* Game State Evaluation
* Input Validation and Error Handling

---

## Example Output

```
   1   2   3
1  X | O | X
  ---+---+---
2    | X |  
  ---+---+---
3  O |   | O
```

---

## Future Improvements

* Add Alpha-Beta pruning for AI optimization
* Implement a graphical UI (e.g., using SFML or Qt)
* Add score tracking system
* Allow customizable board sizes (NxN)

---

## Author

Developed as a C++ OOP and AI practice project.

---
