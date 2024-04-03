#include "board.h"

std::array<std::array<std::array<vision, BOARD::files>, BOARD::ranks>, BOARD::totalNumOfPieces> precompiledPieceVision;

movesInSingleDirection Board::pieceMoveGenerationDirection(INDEX index, direction dir)
{
    movesInSingleDirection moves = {};

    PIECE pieceType = boardIndex(index)->pieceType;

    boardIndex(index)->watchingSquare.erase(dir);

    if (pieceType == PIECE::EMPTY)
        return moves;

    if (pieceType != PIECE::PAWN)
    {
        std::vector<INDEX> singleDirVision = precompiledPieceVision[PIECE_VISION::pieceVisionIndex.find(pieceType)->second][index.rank][index.file][VISION_RELATION::dirIndexRelation.find(dir)->second];
        
        for (auto square : singleDirVision)
        {
            for (auto it : boardIndex(square)->watchers)
            {
                if (it.second == dir)
                    boardIndex(square)->watchers.erase(it.first);
            }
        }

        for (auto square : singleDirVision)
        {
            boardIndex(square)->watchers[index] = dir;
            boardIndex(index)->watchingSquare[dir].push_back(square);
            if (boardIndex(square)->color == boardIndex(index)->color)
                break;
            else
            {
                if (boardIndex(square)->isEmpty)
                {
                    moves.push_back({MOVE::remainingMovesIndex, square});
                    continue;
                }
                else
                {
                    if (boardIndex(square)->pieceType == PIECE::KING)
                        moves.push_back({MOVE::checksIndex, square});
                    else
                        moves.push_back({MOVE::capturesIndex, square});
                    break;
                }
            }
        }
    }

    else
    {
        std::vector<INDEX> singleDirVision = precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][index.rank][index.file][dir[VISION_RELATION::pawnDirDiffIndex]];

        int it = 0;
        if (boardIndex(index)->color == COLOR::black)
            it = 4;

        for (auto square : singleDirVision)
        {
            for (auto it : boardIndex(square)->watchers)
            {
                if (it.second == dir)
                    boardIndex(square)->watchers.erase(it.first);
            }
        }

        for (auto square : singleDirVision)
        {
            if (VISION_RELATION::whitePawnMoveIndex + it == dir[VISION_RELATION::pawnDirDiffIndex])
            {
                boardIndex(square)->watchers[index] = dir;
                boardIndex(index)->watchingSquare[dir].push_back(square);

                if (boardIndex(square)->isEmpty)
                {
                    moves.push_back({MOVE::remainingMovesIndex, square});
                }
                else
                    break;
            }
            else if (VISION_RELATION::whitePawnCaptureIndex + it == dir[VISION_RELATION::pawnDirDiffIndex])
            {
                boardIndex(square)->watchers[index] = dir;
                boardIndex(index)->watchingSquare[dir].push_back(square);
                if (boardIndex(square)->color == -boardIndex(index)->color)
                {
                    if (boardIndex(square)->pieceType == PIECE::KING)
                        moves.push_back({MOVE::checksIndex, square});
                    else
                        moves.push_back({MOVE::capturesIndex, square});
                }
            }
            else if (VISION_RELATION::whitePromotionCaptureIndex + it == dir[VISION_RELATION::pawnDirDiffIndex])
            {
                boardIndex(square)->watchers[index] = dir;
                boardIndex(index)->watchingSquare[dir].push_back(square);
                if (boardIndex(square)->color == -boardIndex(index)->color)
                {
                    if (boardIndex(square)->pieceType == PIECE::KING)
                        moves.push_back({MOVE::checksIndex, square});
                    else
                        moves.push_back({MOVE::promotionIndex, square});
                }
            }
            else if (VISION_RELATION::whitePromotionMoveIndex + it == dir[VISION_RELATION::pawnDirDiffIndex])
            {
                boardIndex(square)->watchers[index] = dir;
                boardIndex(index)->watchingSquare[dir].push_back(square);
                if (boardIndex(square)->isEmpty)
                {
                    moves.push_back({MOVE::promotionIndex, square});
                }
            }
        }
    }

    return moves;
}
