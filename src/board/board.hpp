#include <vector>
#include <string>
#include <sstream>

enum class PieceType
{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

struct Piece
{
    PieceType piece_type;
    int index;
    std::vector<std::vector<int>> vision;
};

int squareNameToIndex (std::string square)
{
    return 0;
}

class Board
{
    int board[64];
    bool castle[4] = {false, false, false, false};
    int enpassent;
    int fifty_moves;
    int materialBalance;
    int turn; // white = 1   black = -1
    std::string FEN;
    Piece white_pieces[33];
    Piece black_pieces[33];

public:
    Board(std::string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1")
    {
        // some code to convert fen string to the above members
        std::istringstream iss(fen);
        std::vector<std::string> modified_fen;

        do
        {
            std::string subs;
            iss >> subs;
            modified_fen.push_back(subs);
        } while (iss);

        int board2D[8][8];
        int file = 0, rank = 7;
        int piece_id = 1;
        for (char s : modified_fen[0])
        {
            switch (s)
            {
            case 'p':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::PAWN;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'n':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::KNIGHT;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'b':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::BISHOP;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'r':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::ROOK;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'q':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::QUEEN;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'k':
                board2D[rank][file] = piece_id;
                piece_id++;
                black_pieces[piece_id].piece_type = PieceType::KING;
                black_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'P':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::PAWN;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'N':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::KNIGHT;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'B':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::BISHOP;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'R':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::ROOK;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'Q':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::QUEEN;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case 'K':
                board2D[rank][file] = piece_id;
                piece_id++;
                white_pieces[piece_id].piece_type = PieceType::KING;
                white_pieces[piece_id].index = (rank * 8) + file;
                break;
            case '/':
                file = 0;
                rank--;
                break;
            default:
                int num = s - '0';
                file += num;
                for (int i = file; i < file + num; i++)
                    board2D[rank][i] = 0;
                break;
            }
        }
        int count1D = 0;
        for (int i = 7; i >= 0; i--)
        {
            for (int j = 0; j < 8; j++)
            {
                board[count1D] = board2D[i][j];
                count1D++;
            }
        }

        if (modified_fen[1] == "w")
            turn = 1;
        else
            turn = -1;


        for (char s : modified_fen[2])
        {
            switch (s)
            {
            case 'K':
                castle[0] = true;
                break;
            case 'Q':
                castle[1] = true;
                break;
            case 'k':
                castle[2] = true;
                break;
            case 'q':
                castle[3] = true;
                break;
            }
        }

        if (modified_fen[3] == "-")
            enpassent = -1;
        else {
            enpassent = squareNameToIndex(modified_fen[3]);
        }

        fifty_moves = stoi(modified_fen[4]);

    }

    void move_generation()
    {
        // return all posible move
    }

    void update()
    {
        // some code to update the board
    }
};