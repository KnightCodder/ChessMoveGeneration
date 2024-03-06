#include "board.h"

void Board::update(int from[], int to[])
{
    int rank_from = from[0];
    int file_from = from[1];
    int rank_to = to[0];
    int file_to = to[1];
    int index_from = (8 * rank_from) + file_from;
    int index_to = (8 * rank_to) + file_to;
    PieceType piece_from = board[rank_from][file_from].piece_type;
    PieceType piece_to = board[rank_to][file_to].piece_type;

    // changing board
    {
        std::swap(board[rank_to][file_to], board[rank_from][file_from]);
        board[rank_to][file_to].index = index_to;
        board[rank_to][file_to].vision = piece_vision(to);

        board[rank_from][file_from].isEmpty = true;
        board[rank_from][file_from].color = 0;
        board[rank_from][file_from].piece_type = PieceType::EMPTY;
        board[rank_from][file_from].index = index_from;
        board[rank_from][file_from].vision = {};
    }

    // changing Pboard
    {
        Pboard[rank_to][file_to] = Pboard[rank_from][file_from];
        Pboard[rank_from][file_from] = '*';
    }

    // castle
    {
        if (index_from == 4 || index_from == 7 || index_to == 7)
            castle[0] = false;
        if (index_from == 4 || index_from == 0 || index_to == 0)
            castle[1] = false;
        if (index_from == 60 || index_from == 63 || index_to == 63)
            castle[2] = false;
        if (index_from == 60 || index_from == 56 || index_to == 56)
            castle[3] = false;
    }
    // enpassent
    {
        if (piece_from == PieceType::PAWN && ((rank_from == 1 && rank_to == 3) || (rank_from == 6 && rank_to == 4)))
        {
            if (((file_to > 0 && board[rank_to][file_to - 1].piece_type == PieceType::PAWN) || (file_to < 7 && board[rank_to][file_to + 1].piece_type == PieceType::PAWN)) && board[rank_to][file_to].color * board[rank_to][file_to - 1].color < 0)
            {
                enpassent = {(rank_from + rank_to) / 2, file_to};
            }
        }
    }
    // fifty_moves
    {
        fifty_moves++;
        if (piece_from == PieceType::PAWN)
            fifty_moves = 0;
        if (piece_to != PieceType::EMPTY)
            fifty_moves = 0;
    }
    // materialBalance

    // turn
    turn *= -1;

    // white king check vision
    {
        if (piece_from == PieceType::KING && turn == black_turn)
        {
            white_king_check_vision[0] = king_vision(to);
            white_king_check_vision[1] = rook_vision(to);
            white_king_check_vision[2] = bishop_vision(to);
            white_king_check_vision[3] = knight_vision(to);
            white_king_check_vision[4] = pawn_vision(to, white_turn);
        }
    }

    // black king check vision
    {
        if (piece_from == PieceType::KING && turn == white_turn)
        {
            black_king_check_vision[0] = king_vision(to);
            black_king_check_vision[1] = rook_vision(to);
            black_king_check_vision[2] = bishop_vision(to);
            black_king_check_vision[3] = knight_vision(to);
            black_king_check_vision[4] = pawn_vision(to, black_turn);
        }
    }
}
