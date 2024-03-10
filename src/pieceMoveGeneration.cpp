#include "board.h"

std::array<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>, 6> Board::piece_move_generation(int rank, int file)
{
    // zero index would store checks
    // first index would store captures
    // second index would store castle
    // third index would store enpassent
    // forth index would store promotion
    // fifth index would store rest of the moves

    std::array<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>, 6> generated_moves = {};
    int piece_color = board[rank][file].color;
    PieceType piece_type = board[rank][file].piece_type;

    if (piece_type == PieceType::EMPTY)
    {
        return {};
    }
    if (piece_type == PieceType::KING)
    {
        if (castle[0] && piece_color == white_turn)
        {
            board[0][6].relatives.insert(&board[rank][file]);
            if (board[0][6].isEmpty && board[0][5].isEmpty)
                generated_moves[2].push_back({{0, 4}, {0, 6}});
        }
        if (castle[1] && piece_color == white_turn)
        {
            board[0][6].relatives.insert(&board[rank][file]);
            if (board[0][3].isEmpty && board[0][2].isEmpty && board[0][1].isEmpty)
                generated_moves[2].push_back({{0, 4}, {0, 2}});
        }
        if (castle[2] && piece_color == black_turn)
        {
            board[0][6].relatives.insert(&board[rank][file]);
            if (board[7][5].isEmpty && board[7][6].isEmpty)
                generated_moves[2].push_back({{7, 4}, {7, 6}});
        }
        if (castle[3] && piece_color == black_turn)
        {
            board[0][6].relatives.insert(&board[rank][file]);
            if (board[7][3].isEmpty && board[7][2].isEmpty && board[7][1].isEmpty)
                generated_moves[2].push_back({{7, 4}, {7, 2}});
        }
    }

    for (int i = 0; i < 8; i++)
    {
        for (auto j : board[rank][file].vision[i])
        {
            j->relatives.insert(&board[rank][file]);
            int j_rank = j->index / 8;
            int j_file = j->index - (8 * j_rank);
            if (j->color == piece_color)
                break;
            // make board[rank][file] piece wise not color wise

            if (piece_type == PieceType::PAWN)
            {
                if (i == 0 && j->color == 0)
                {
                    generated_moves[5].push_back({{rank, file}, {j_rank, j_file}});
                }
                else if (i == 1 && j->color == -piece_color)
                {
                    if (j->piece_type == PieceType::KING)
                        generated_moves[0].push_back({{rank, file}, {j_rank, j_file}});
                    else
                        generated_moves[1].push_back({{rank, file}, {j_rank, j_file}});
                }
                else if ((i == 2 && j->color == 0) || (i == 3 && j->color == -piece_color))
                {
                    if (j->piece_type == PieceType::KING)
                        generated_moves[0].push_back({{rank, file}, {j_rank, j_file}});
                    else
                        generated_moves[4].push_back({{rank, file}, {j_rank, j_file}});
                }
                if (j_rank == enpassent[0] && j_file == enpassent[1])
                    generated_moves[3].push_back({{rank, file}, {j_rank, j_file}});
            }

            else
            {
                if (j->color == -piece_color)
                {
                    if (j->piece_type == PieceType::KING)
                        generated_moves[0].push_back({{rank, file}, {j_rank, j_file}});
                    else
                        generated_moves[1].push_back({{rank, file}, {j_rank, j_file}});
                    break;
                }
                else
                {
                    generated_moves[5].push_back({{rank, file}, {j_rank, j_file}});
                }
            }
        }
    }

    return generated_moves;
}
