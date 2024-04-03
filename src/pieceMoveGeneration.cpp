#include "board.h"

movesOfaPiece Board::pieceMoveGeneration(INDEX index)
{
    movesOfaPiece moves = {};

    if (boardIndex(index)->pieceType == PIECE::EMPTY)
        return moves;
    if (boardIndex(index)->pieceType == PIECE::PAWN)
    {
        for (int dir = 0; dir < VISION_RELATION::maxNumOfMoveDirection; dir++)
            moves[{VISION_RELATION::pawnDirZeroIndexVal, dir}] = pieceMoveGenerationDirection(index, {VISION_RELATION::pawnDirZeroIndexVal, dir});
    }
    else if (boardIndex(index)->pieceType == PIECE::KNIGHT)
    {
        for (int i = 0; i < VISION_RELATION::maxNumOfMoveDirection; i++)
            moves[VISION_RELATION::knightIndexDiff[i]] = pieceMoveGenerationDirection(index, VISION_RELATION::knightIndexDiff[i]);
    }
    else
    {
        for (int i = 0; i < VISION_RELATION::maxNumOfMoveDirection; i++)
            moves[VISION_RELATION::kqrbIndexDiff[i]] = pieceMoveGenerationDirection(index, VISION_RELATION::kqrbIndexDiff[i]);
    }

    return moves;
}
