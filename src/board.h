// src/Board/board.h
#ifndef BOARD_H_INCLUDED
#define BOARD_H_INCLUDED

#include <vector>
#include <string>
#include <sstream>
#include <array>
#include <set>
#include <iostream>
#include "piece.h"

enum class GameStatus
{
    STILL_GOING,
    DRAW,
    STALEMATE,
    INSUFFICIENT_MATERIAL,
    WHITE_WINS,
    BLACK_WINS
};

inline std::array<int, 2> squareNameToIndex(std::string square)
{
    int file = square[0] - 'a';
    int rank = square[1] - '1';

    return {rank, file};
}

inline std::string indexToSquareName(std::array<int, 2> index)
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

class Board
{
    Piece board[8][8] = {}; // have piece_data
    char Pboard[8][8] = {};
    bool castle[4] = {};
    std::array<int, 2> enpassent = {-1, -1};
    int fifty_moves = 0;
    int materialBalance = 0;
    int turn = 0;
    bool isCheck = false;
    bool illegal = false;
    GameStatus status = GameStatus::STILL_GOING;

    std::string FEN = "";
    std::array<std::vector<Piece *>, 8> white_king_check_vision[5];
    std::array<std::vector<Piece *>, 8> black_king_check_vision[5];
    std::array<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>, 6> moves = {};

public:
    std::array<std::vector<Piece *>, 8> bishop_vision(int index[]);
    std::array<std::vector<Piece *>, 8> knight_vision(int index[]);
    std::array<std::vector<Piece *>, 8> rook_vision(int index[]);
    std::array<std::vector<Piece *>, 8> queen_vision(int index[]);
    std::array<std::vector<Piece *>, 8> king_vision(int index[]);
    std::array<std::vector<Piece *>, 8> pawn_vision(int index[], int color);
    std::array<std::vector<Piece *>, 8> piece_vision(int index[]);
    std::array<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>, 6> piece_move_generation(int rank, int file);

    void update(int from[], int to[], bool isCastle = false);
    bool Check();

    void generateMoves();

    void temp_promote(PieceType piece, int index[2])
    {
        board[index[0]][index[1]].piece_type = piece;
    }

    void printBoard()
    {
        for (int rank = 7; rank >= 0; rank--)
        {
            for (int file = 0; file < 8; file++)
            {
                std::cout << Pboard[rank][file] << " ";
            }
            std::cout << '\n';
        }
        std::cout << std::endl;

        std::cout << "castle : " << castle[0] << castle[1] << castle[2] << castle[3] << std::endl;
        std::cout << "enpassent : " << indexToSquareName(enpassent) << std::endl;
        std::cout << "fifty moves : " << fifty_moves << std::endl;
        std::cout << "turn : " << turn << std::endl;
        std::cout << "FEN : " << FEN << std::endl;
        std::cout << "isCheck : " << isCheck << std::endl;
        std::cout << "illegal : " << illegal << std::endl;

        // for (int rank = 7; rank >= 0; rank--)
        // {
        //     for (int file = 0; file < 8; file++)
        //     {
        //         std::cout << rank  << "  " << file << "  " << static_cast<int>(board[rank][file].piece_type) << std::endl;
        //         for(auto i : board[rank][file].vision)
        //         {
        //             for(auto j : i)
        //             {
        //                 std::cout << j->index << " ";
        //             }
        //             std::cout << "--------------------------------\n";
        //         }
        //         std::cout << '\n';
        //     }
        // }

        // for (int i = 0; i < 5; i++)
        // {
        //     for (auto j : white_king_check_vision[i])
        //     {
        //         for (auto k : j)
        //         {
        //             std::cout << k->index << " ";
        //         }
        //         std::cout << "--------------------------------\n";
        //     }
        //     std::cout << '\n';
        // }

        // for (int rank = 0; rank < 8; rank++)
        // {
        //     for (int file = 0; file < 8; file++)
        //     {
        //         for (int i = 0; i < 6; i++)
        //         {
        //             for (auto j : board[rank][file].moves[i])
        //             {
        //                 std::cout << "rank-" << rank << " file-" << file << " type-" << i << " move :- " << j.first.first << "_" << j.first.second << "  " << j.second.first << "_" << j.second.second << std::endl;
        //             }
        //         }
        //     }
        // }

        for (int i = 0; i < 6; i++)
        {
            for (auto j : moves[i])
            {
                std::cout << "type-" << i << " move :- " << j.first.first << "_" << j.first.second << "  " << j.second.first << "_" << j.second.second << std::endl;
            }
        }
    }

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
            int index[] = {rank, file};

            switch (s)
            {
            case 'p':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::PAWN;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = pawn_vision(index, black_turn);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;
            case 'n':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::KNIGHT;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = knight_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'b':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::BISHOP;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = bishop_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'r':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::ROOK;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = rook_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'q':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::QUEEN;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = queen_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'k':
                board[rank][file].color = black_turn;
                board[rank][file].piece_type = PieceType::KING;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                Pboard[rank][file] = s;

                board[rank][file].vision = king_vision(index);

                black_king_check_vision[0] = king_vision(index);
                black_king_check_vision[1] = rook_vision(index);
                black_king_check_vision[2] = bishop_vision(index);
                black_king_check_vision[3] = knight_vision(index);
                black_king_check_vision[4] = pawn_vision(index, black_turn);

                file++;
                piece_id++;
                break;

            case 'P':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::PAWN;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = pawn_vision(index, white_turn);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;
            case 'N':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::KNIGHT;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = knight_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'B':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::BISHOP;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = bishop_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'R':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::ROOK;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = rook_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'Q':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::QUEEN;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                board[rank][file].vision = queen_vision(index);
                Pboard[rank][file] = s;
                file++;
                piece_id++;
                break;

            case 'K':
                board[rank][file].color = white_turn;
                board[rank][file].piece_type = PieceType::KING;
                board[rank][file].index = (rank * 8) + file;
                board[rank][file].isEmpty = false;
                Pboard[rank][file] = s;
                board[rank][file].vision = king_vision(index);

                white_king_check_vision[0] = king_vision(index);
                white_king_check_vision[1] = rook_vision(index);
                white_king_check_vision[2] = bishop_vision(index);
                white_king_check_vision[3] = knight_vision(index);
                white_king_check_vision[4] = pawn_vision(index, white_turn);

                file++;
                piece_id++;
                break;

            case '/':
                file = 0;
                rank--;
                break;
            default:
                int num = s - '0';
                for (int i = file; i < file + num; i++)
                {
                    Pboard[rank][i] = '*';
                    board[rank][i].index = (rank * 8) + i;
                }

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

        // moves
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                board[rank][file].moves = piece_move_generation(rank, file);
            }
        }

        Check();

        generateMoves();
    }

    ~Board()
    {
        std::cout << "board is deleted" << std::endl;
    }
};

#endif // BOARD_H_INCLUDED
