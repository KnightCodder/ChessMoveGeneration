#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <iostream>

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
    bool isEmpty = true;
    PieceType piece_type;
    int index;
    std::vector<std::vector<int>> vision;
};

std::array<int, 2> squareNameToIndex(std::string square)
{
    int file = square[0] - 'a';
    int rank = square[1] - '1';

    return {rank, file};
}

std::string indexToSquareName(std::array<int, 2> index)
{
    if (index[0] == -1)
        return "nil";

    char file = (char)(index[1] + 'a');
    char rank = (char)(index[0] + '1');

    std::string squareName;
    squareName.push_back(file);
    squareName.push_back(rank);

    return squareName;
}

const int white_turn = 1;
const int black_turn = -1;
const std::string default_fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const std::string whitepiece_char = "*PNBRQK";
const std::string blackpiece_char = "*pnbrqk";

class Board
{
    int board[8][8] = {};
    bool castle[4] = {};
    std::array<int, 2> enpassent;
    int fifty_moves;
    int materialBalance;
    int turn;
    std::string FEN;
    Piece white_pieces[33];
    Piece black_pieces[33];

public:
    Board(std::string fen = default_fen)
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

        int file = 0, rank = 7;
        int piece_id = 1;
        for (char s : modified_fen[0])
        {
            switch (s)
            {
            case 'p':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::PAWN;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'n':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::KNIGHT;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;

            case 'b':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::BISHOP;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'r':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::ROOK;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'q':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::QUEEN;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'k':
                board[rank][file] = piece_id;
                black_pieces[piece_id].piece_type = PieceType::KING;
                black_pieces[piece_id].index = (rank * 8) + file;
                black_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'P':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::PAWN;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'N':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::KNIGHT;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'B':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::BISHOP;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'R':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::ROOK;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'Q':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::QUEEN;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case 'K':
                board[rank][file] = piece_id;
                white_pieces[piece_id].piece_type = PieceType::KING;
                white_pieces[piece_id].index = (rank * 8) + file;
                white_pieces[piece_id].isEmpty = false;
                file++;
                piece_id++;
                break;
            case '/':
                file = 0;
                rank--;
                break;
            default:
                int num = s - '0';
                file += num;
                break;
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
            enpassent = {-1, -1};
        else
        {
            enpassent = squareNameToIndex(modified_fen[3]);
        }

        fifty_moves = stoi(modified_fen[4]);
        FEN = fen;
    }

    void printBoard()
    {
        for (int rank = 7; rank >= 0; rank--)
        {
            for (int file = 0; file < 8; file++)
            {
                int piece_id = board[rank][file];
                // std::cout << "rank : " << rank << " file : " << file << " piece_id : " << piece_id << std::endl;

                if (!white_pieces[piece_id].isEmpty)
                {
                    int piece = static_cast<int>(white_pieces[piece_id].piece_type);
                    std::cout << whitepiece_char[piece] << ' ';
                    continue;
                }
                if (!black_pieces[piece_id].isEmpty)
                {
                    int piece = static_cast<int>(black_pieces[piece_id].piece_type);
                    std::cout << blackpiece_char[piece] << ' ';
                    continue;
                }
                std::cout << "* ";
            }
            std::cout << '\n';
        }
        std::cout << std::endl;

        std::cout << "castle : " << castle[0] << castle[1] << castle[2] << castle[3] << std::endl;
        std::cout << "enpassent : " << indexToSquareName(enpassent) << std::endl;
        std::cout << "fifty moves : " << fifty_moves << std::endl;
        std::cout << "turn : " << turn << std::endl;
        std::cout << "FEN : " << FEN << std::endl;
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