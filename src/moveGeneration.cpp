#include "board.h"

totalMoves Board::moveGeneration()
{
    totalMoves moves;
    illegal = false;
    checks = 0;

    for (int rank = 0; rank < BOARD::ranks; rank++)
    {
        for (int file = 0; file < BOARD::files; file++)
        {
            {
                for (auto i : boardIndex(INDEX(rank, file))->moves)
                {
                    for (auto j : i.second)
                        if (boardIndex(INDEX(rank, file))->color == turn)
                        {
                            moves[j.first].push_back({{rank, file}, j.second});
                            if (j.first == 0)
                                illegal = true;
                        }
                        else
                        {
                            if (j.first == 0)
                                checks++;
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

    // castle
    if (checks == 0)
    {
        if (turn == TURN::white)
        {
            if (castle[BOARD::whiteKingSideCastleIndex])
            {
                if (boardIndex(INDEX(0,5))->isEmpty && boardIndex(INDEX(0,6))->isEmpty)
                {
                    if (attackers(INDEX(0,5), COLOR::black) == 0 && attackers(INDEX(0,6), COLOR::black) == 0)
                        moves[MOVE::castleIndex].push_back({INDEX(0,4),INDEX(0,6)});
                }
            }
            if (castle[BOARD::whiteQueenSideCastleIndex])
            {
                if (boardIndex(INDEX(0,3))->isEmpty && boardIndex(INDEX(0,2))->isEmpty && boardIndex(INDEX(0,1))->isEmpty)
                {
                    if (attackers(INDEX(0,3), COLOR::black) == 0 && attackers(INDEX(0,2), COLOR::black) == 0)
                        moves[MOVE::castleIndex].push_back({INDEX(0,4),INDEX(0,2)});
                }
            }
        }
        else if (turn == TURN::black)
        {
            if (castle[BOARD::blackKingSideCastleIndex])
            {
                if (boardIndex(INDEX(7,5))->isEmpty && boardIndex(INDEX(7,6))->isEmpty)
                {
                    if (attackers(INDEX(7,5), COLOR::white) == 0 && attackers(INDEX(7,6), COLOR::white) == 0)
                        moves[MOVE::castleIndex].push_back({INDEX(7,4),INDEX(7,6)});
                }
            }
            if (castle[BOARD::blackKingSideCastleIndex])
            {
                if (boardIndex(INDEX(7,3))->isEmpty && boardIndex(INDEX(7,2))->isEmpty && boardIndex(INDEX(7,1))->isEmpty)
                {
                    if (attackers(INDEX(7,3), COLOR::white) == 0 && attackers(INDEX(7,2), COLOR::white) == 0)
                        moves[MOVE::castleIndex].push_back({INDEX(7,4),INDEX(7,2)});
                }
            }
        }
    }

    return moves;
}
