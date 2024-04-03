#include "defination.h"

extern std::array<std::array<std::array<vision, BOARD::files>, BOARD::ranks>, BOARD::totalNumOfPieces> precompiledPieceVision;

void compilingPieceVision()
{
    // Start measuring time
    auto start = std::chrono::high_resolution_clock::now();

    for (int rank = 0; rank < BOARD::ranks; rank++)
    {
        for (int file = 0; file < BOARD::files; file++)
        {
            int brqRank, brqFile;
            int pawnRank, pawnFile;

            // pawn
            {
                pawnRank = rank;
                pawnFile = file;

                if (pawnRank < 6 && pawnRank > 0)
                {
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePawnMoveIndex].push_back({static_cast<int>(pawnRank + 1), pawnFile});
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPawnMoveIndex].push_back({static_cast<int>(6 - pawnRank), pawnFile});
                    if (pawnFile < 7)
                    {
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePawnCaptureIndex].push_back({static_cast<int>(pawnRank + 1), static_cast<int>(pawnFile + 1)});
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPawnCaptureIndex].push_back({static_cast<int>(6 - pawnRank), static_cast<int>(pawnFile + 1)});
                    }
                    if (pawnFile > 0)
                    {
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePawnCaptureIndex].push_back({static_cast<int>(pawnRank + 1), static_cast<int>(pawnFile - 1)});
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPawnCaptureIndex].push_back({static_cast<int>(6 - pawnRank), static_cast<int>(pawnFile - 1)});
                    }
                }
                if (pawnRank == 1)
                {
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePawnMoveIndex].push_back({static_cast<int>(pawnRank + 2), pawnFile});
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPawnMoveIndex].push_back({static_cast<int>(5 - pawnRank), pawnFile});
                }
                if (pawnRank == 6)
                {
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePromotionMoveIndex].push_back({static_cast<int>(pawnRank + 1), pawnFile});
                    precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPromotionMoveIndex].push_back({static_cast<int>(6 - pawnRank), pawnFile});
                    if (pawnFile < 7)
                    {
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePromotionCaptureIndex].push_back({static_cast<int>(pawnRank + 1), static_cast<int>(pawnFile + 1)});
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPromotionCaptureIndex].push_back({static_cast<int>(6 - pawnRank), static_cast<int>(pawnFile + 1)});
                    }
                    if (pawnFile > 0)
                    {
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][rank][file][VISION_RELATION::whitePromotionCaptureIndex].push_back({static_cast<int>(pawnRank + 1), static_cast<int>(pawnFile - 1)});
                        precompiledPieceVision[PIECE_VISION::pawnVisionsIndex][7 - rank][file][VISION_RELATION::blackPromotionCaptureIndex].push_back({static_cast<int>(6 - pawnRank), static_cast<int>(pawnFile - 1)});
                    }
                }
            }

            for (int dir = 0; dir < VISION_RELATION::maxNumOfMoveDirection; dir++)
            {
                // bishop, rook, queen
                {
                    brqRank = rank;
                    brqFile = file;
                    for (int move = 0; move < VISION_RELATION::maxNumOfMovesInOneDirection; move++)
                    {
                        brqRank += VISION_RELATION::kqrbIndexDiff[dir][SQUARE::rankIndex];
                        brqFile += VISION_RELATION::kqrbIndexDiff[dir][SQUARE::fileIndex];

                        if (SQUARE::isInvalidIndex(brqRank, brqFile))
                            break;

                        if (dir < VISION_RELATION::upRightIndex)
                        {
                            precompiledPieceVision[PIECE_VISION::rookVisionsIndex][rank][file][dir].push_back({brqRank, brqFile});
                            precompiledPieceVision[PIECE_VISION::queenVisionsIndex][rank][file][dir].push_back({brqRank, brqFile});
                        }
                        else
                        {
                            precompiledPieceVision[PIECE_VISION::bishopVisionsIndex][rank][file][dir].push_back({brqRank, brqFile});
                            precompiledPieceVision[PIECE_VISION::queenVisionsIndex][rank][file][dir].push_back({brqRank, brqFile});
                        }
                    }
                }

                // knight
                {
                    int knightRank = rank + VISION_RELATION::knightIndexDiff[dir][SQUARE::rankIndex];
                    int knightFile = file + VISION_RELATION::knightIndexDiff[dir][SQUARE::fileIndex];

                    if (!SQUARE::isInvalidIndex(knightRank, knightFile))
                        precompiledPieceVision[PIECE_VISION::knightVisionsIndex][rank][file][dir].push_back(INDEX{knightRank,knightFile});
                }

                // king
                {
                    int kingRank = rank + VISION_RELATION::kqrbIndexDiff[dir][SQUARE::rankIndex];
                    int kingFile = file + VISION_RELATION::kqrbIndexDiff[dir][SQUARE::fileIndex];

                    if (!SQUARE::isInvalidIndex(kingRank, kingFile))
                        precompiledPieceVision[PIECE_VISION::kingVisionsIndex][rank][file][dir].push_back({kingRank, kingFile});
                }
            }
        }
    }

    // Stop measuring time
    auto end = std::chrono::high_resolution_clock::now();

    // Calculate the duration in nanoseconds
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    // Output the duration
    std::cout << "Execution time: " << duration.count() << " nanoseconds" << std::endl;

    // Calculate the size of precompiledPieceVision
    size_t size = sizeof(precompiledPieceVision);

    std::cout << "Size of precompiledPieceVision: " << size << " bytes" << std::endl;
}
