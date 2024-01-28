#include <vector>
#include <string>

enum class PieceType{
    EMPTY, PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING
};

struct Piece{
    PieceType piece_type;
    int index;
    std::vector<std::vector<int>> vision;
};

class Board {
    int board[64];
    bool castle[4];
    int enpassent;
    float fifty_moves;
    int materialBalance;
    std::string FEN;
    Piece white_pieces[32];
    Piece black_pieces[32];

public:
    Board(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1") {
        // some code to convert fen string to the above members
    }

    void move_generation() {
        // return all posible move
    }

    void update() {
        // some code to update the board
    }
};