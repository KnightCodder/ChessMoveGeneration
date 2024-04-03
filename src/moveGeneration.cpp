#include "board.h"

totalMoves Board::moveGeneration()
{
    totalMoves moves;

    for (int rank = 0; rank < BOARD::ranks; rank++)
    {
        for (int file = 0; file < BOARD::files; file++)
        {
            if (board[rank][file].color == turn)
            {
                for(auto i : board[rank][file].moves)
                {
                    for (auto j : i.second)
                    {
                        moves[j.first].push_back({{rank, file},j.second});
                    }
                }
            }
        }
    }

    // enpassent
    if (!enpassent.isEmpty())
    {
        int commonRank = enpassent.rank - turn;
        int leftFile = enpassent.file - 1;
        int rightFile = enpassent.file + 1;
        if (enpassent.file > 0 && board[commonRank][leftFile].color == turn && board[commonRank][leftFile].pieceType == PIECE::PAWN)
        {
            moves[MOVE::enpassentIndex].push_back({INDEX{commonRank, leftFile}, enpassent});
        }
        if (enpassent.file < 7 && board[commonRank][rightFile].color == turn && board[commonRank][rightFile].pieceType == PIECE::PAWN)
        {
            moves[MOVE::enpassentIndex].push_back({INDEX{commonRank, rightFile}, enpassent});
        }
    }

    return moves;
}
