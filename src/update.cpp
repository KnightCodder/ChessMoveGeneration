#include "board.h"

void Board::update(int from[], int to[], bool isCastle)
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

    // changing relative of pieces that the captured piece used to see
    {
        for (auto i : board[rank_to][file_to].moves)
        {
            for (auto j : i)
            {
                board[j.second.first][j.second.second].delete_relative(&board[rank_to][file_to]);
            }
        }
    }

    {
        for (auto i : board[rank_from][file_from].relatives)
        {
            int relative_index = i->index;
            int relative_rank = relative_index / 8;
            int relative_file = relative_index - (8 * relative_rank);
            i->moves = piece_move_generation(relative_rank, relative_file);
        }
    }

    // changing moves of relative pieces
    {
        std::set<Piece *> temp = board[rank_to][file_to].relatives;
        board[rank_to][file_to].relatives = {};

        for (auto i : temp)
        {
            int relative_index = i->index;
            int relative_rank = relative_index / 8;
            int relative_file = relative_index - (8 * relative_rank);

            i->moves = piece_move_generation(relative_rank, relative_file);
        }
    }

    // generating moves of at new location for the piece
    {
        board[rank_to][file_to].moves = piece_move_generation(rank_to, file_to);
    }

    // changing Pboard
    {
        Pboard[rank_to][file_to] = Pboard[rank_from][file_from];
        Pboard[rank_from][file_from] = '*';
    }

    if (isCastle) // use it after rook move so that turn , fifty moves, and other things dont change without any reason
        return;

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
        if (enpassent[0] != -1)
        {
            int enpassent_rank = enpassent[0];
            int enpassent_file = enpassent[1];

            enpassent = {-1, -1};

            for (auto i : board[enpassent_rank][enpassent_file].relatives)
            {
                if (i->piece_type != PieceType::PAWN)
                    continue;

                int relative_index = i->index;
                int relative_rank = relative_index / 8;
                int relative_file = relative_index - (8 * relative_rank);

                i->moves = piece_move_generation(relative_rank, relative_file);
            }
        }

        if (piece_from == PieceType::PAWN && ((rank_from == 1 && rank_to == 3) || (rank_from == 6 && rank_to == 4)))
        {
            if (((file_to > 0 && board[rank_to][file_to - 1].piece_type == PieceType::PAWN) || (file_to < 7 && board[rank_to][file_to + 1].piece_type == PieceType::PAWN)) && (board[rank_to][file_to].color * board[rank_to][file_to - 1].color < 0 || board[rank_to][file_to].color * board[rank_to][file_to + 1].color < 0))
            {
                enpassent = {(rank_from + rank_to) / 2, file_to};
                if (file_to < 7)
                    board[rank_to][file_to + 1].moves = piece_move_generation(rank_to, file_to + 1);
                if (file_to > 0)
                    board[rank_to][file_to - 1].moves = piece_move_generation(rank_to, file_to - 1);
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
    isCheck = false;
    illegal = false;
    Check();

    // generate moves
    moves = {};
    generateMoves();
}
