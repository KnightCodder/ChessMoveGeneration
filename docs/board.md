# board.hpp

This header file defines a C++ chess board representation with functionality for move generation and updating the board. The board is initialized using a FEN (Forsyth-Edwards Notation) string.

## Usage

To use this chess board implementation, include the "board.hpp" header file in your C++ project. You can then create an instance of the `Board` class by providing an optional FEN string during initialization.

```cpp
#include "board.hpp"

int main() {
    // Initialize the board with a default or custom FEN string
    Board chessBoard;
    
    // Your code here...

    return 0;
}
```


## Board Class

### Members

* `int board[64]`: represents the chessboard as a flat array of 64 squares. each square has a value as piece_id.
* `bool castle[4]`: Tell us if castle is possible or not
    - index 0 : true if white has right to castle king side
    - index 1 : true if white has right to castle queen side
    - index 2 : true if black has right to castle king side
    - index 3 : true if black has right to castle queen side
* `int enpassent`: index of a square where enpassent is possible. if enpassent is not possible then it would have a value of -1.
* `int fifty_moves`: counter for the fifty-move rule. if the move is not capture or a pawn move then it gets an increament of 1. and after a pawn moves or capture happens it get the value 0. if fifty_moves == 100 then the game ends in a draw.
* `materialBalance`: Keeps track of the material balance in the game.
* `std::string FEN`: current FEN string representing the board state. the default value would be empty , it would only get updated if we wanted to. this is to make the engine faster.
* `Piece white_pieces[33]`: the index of this would be an piece_id and the value would be the piece data. the piece_ids would be unique no matter what the colour is thats why it has a size of 32 instead of 16. the index 0 is stored for empty.
* `Piece black_pieces[33]`: similair to white_pieces.

### Methods

* `Board(std::string fen)`: Constructor to initialize the board with an optional FEN string.
* `void move_generation()`: Function to generate all possible moves on the current board.
* `void update()`: Function to update the board state based on the moves made.

## Contributing

Feel free to contribute to the development of this chess board implementation by submitting issues or pull requests.