#ifndef BASICDEFINATION_H_INCLUDED
#define BASICDEFINATION_H_INCLUDED

#include <iostream>
#include <map>
#include <vector>
#include <array>

#define dimension_of_board 2
#define direction std::array<int, dimension_of_board>
#define vision std::array<std::vector<INDEX>, VISION_RELATION::maxNumOfMoveDirection>
#define movesInSingleDirection std::vector<std::pair<int, INDEX>>
#define movesOfaPiece std::map<direction, movesInSingleDirection>
#define totalMoves std::array<std::vector<std::pair<INDEX, INDEX>>, MOVE::numOfPossibleTypesMoves>
#define watch std::map<INDEX, direction>
#define watching std::map<direction, std::vector<INDEX>>

namespace BOARD
{
    const int ranks = 8;
    const int files = 8;
    const int totalSquares = 64;
    const int totalNumOfPieces = 6;
    const int numOfCastlingRights = 4;
    const int whiteKingSideCastleIndex = 0;
    const int whiteQueenSideCastleIndex = 1;
    const int blackKingSideCastleIndex = 2;
    const int blackQueenSideCastleIndex = 3;

    const std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
}

namespace SQUARE
{
    const int empty = -1;
    const std::string emptyStr = "empty";
    const int rankIndex = 0;
    const int fileIndex = 1;

    inline bool isInvalidIndex(int rank, int file)
    {
        if (rank < 0 || rank > 7 || file < 0 || file > 7)
            return true;
        return false;
    }
}

namespace TURN
{
    const int white = 1;
    const int black = -1;
    const int nothing = 0;
}

enum class GameStatus
{
    STILL_GOING,
    DRAW,
    STALEMATE,
    INSUFFICIENT_MATERIAL,
    WHITE_WINS,
    BLACK_WINS,
    NOT_SURE,
    ILLEGAL
};

enum class PIECE
{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

struct INDEX
{
    int rank = SQUARE::empty;
    int file = SQUARE::empty;

    INDEX(int _rank = SQUARE::empty, int _file = SQUARE::empty)
    {
        if (_rank == SQUARE::empty && _file == SQUARE::empty)
            return;

        setIndex(_rank, _file);
    }

    bool operator<(const INDEX &other) const
    {
        // Compare x first, then y if x's are equal
        if (rank != other.rank)
        {
            return rank < other.rank;
        }
        return file < other.file;
    }

    bool operator==(const INDEX &other) const
    {
        return (rank == other.rank) && (file == other.file);
    }

    bool setIndex(int _rank, int _file, bool exp = false)
    {
        try
        {
            if (SQUARE::isInvalidIndex(_rank, _file))
            {
                if (exp)
                    return false;
                throw std::runtime_error("invalid indices");
            }

            rank = _rank;
            file = _file;
        }
        catch (const std::runtime_error &e)
        {
            std::cerr << "Error : " << e.what() << _rank << "_" << _file << std::endl;
        }
        return true;
    }

    std::string print() const
    {
        if (rank == SQUARE::empty || file == SQUARE::empty)
            return "invalid index";
        std::string index = "";
        index += (char)('a' + file);
        index += (char)('1' + rank);
        return index;
    }

    void strToIndex(std::string index)
    {
        if (index == SQUARE::emptyStr)
        {
            rank = SQUARE::empty;
            file = SQUARE::empty;
            return;
        }

        if (index.length() != 2 || index[0] < 'a' || index[0] > 'h' || index[1] < '1' || index[1] > '8')
        {
            std::cout << "invalid index : " << index << std::endl;
            return;
        }
        rank = index[1] - '1';
        file = index[0] - 'a';
    }

    bool isEmpty()
    {
        if (rank == SQUARE::empty && file == SQUARE::empty)
            return true;
        return false;
    }
};

namespace COLOR
{
    const int white = 1;
    const int black = -1;
    const int nothing = 0;
}

namespace VISION_RELATION
{
    const int maxNumOfMoveDirection = 8;
    const int maxNumOfMovesInOneDirection = 7;

    const int upIndex = 0;
    const int rightIndex = 1;
    const int downIndex = 2;
    const int leftIndex = 3;
    const int upRightIndex = 4;
    const int downRightIndex = 5;
    const int downLeftIndex = 6;
    const int upLeftIndex = 7;

    const direction upDiff = {1, 0};
    const direction upRightDiff = {1, 1};
    const direction rightDiff = {0, 1};
    const direction downRightDiff = {-1, 1};
    const direction downDiff = {-1, 0};
    const direction downLeftDiff = {-1, -1};
    const direction leftDiff = {0, -1};
    const direction upLeftDiff = {1, -1};

    const std::array<direction, maxNumOfMoveDirection> kqrbIndexDiff = {upDiff, rightDiff, downDiff, leftDiff, upRightDiff, downRightDiff, downLeftDiff, upLeftDiff};

    const int up2Right1Index = 0;
    const int up1Right2Index = 1;
    const int down1Right2Index = 2;
    const int down2Right1Index = 3;
    const int down2Left1Index = 4;
    const int down1Left2Index = 5;
    const int up1Left2Index = 6;
    const int up2Left1Index = 7;

    const direction up2Right1Diff = {2, 1};
    const direction up1Right2Diff = {1, 2};
    const direction down1Right2Diff = {-1, 2};
    const direction down2Right1Diff = {-2, 1};
    const direction down2Left1Diff = {-2, -1};
    const direction down1Left2Diff = {-1, -2};
    const direction up1Left2Diff = {1, -2};
    const direction up2Left1Diff = {2, -1};

    const std::array<direction, maxNumOfMoveDirection> knightIndexDiff = {up2Right1Diff, up1Right2Diff, down1Right2Diff, down2Right1Diff, down2Left1Diff, down1Left2Diff, up1Left2Diff, up2Left1Diff};

    const std::map<direction, int> dirIndexRelation = {{upDiff, upIndex}, {rightDiff, rightIndex}, {downDiff, downIndex}, {leftDiff, leftIndex}, {upRightDiff, upRightIndex}, {downRightDiff, downRightIndex}, {downLeftDiff, downLeftIndex}, {upLeftDiff, upLeftIndex}, {up2Right1Diff, up2Right1Index}, {up1Right2Diff, up1Right2Index}, {down1Right2Diff, down1Right2Index}, {down2Right1Diff, down2Right1Index}, {down2Left1Diff, down2Left1Index}, {down1Left2Diff, down1Left2Index}, {up1Left2Diff, up1Left2Index}, {up2Left1Diff, up2Left1Index}};

    const int whitePawnMoveIndex = 0;
    const int whitePawnCaptureIndex = 1;
    const int whitePromotionMoveIndex = 2;
    const int whitePromotionCaptureIndex = 3;
    const int blackPawnMoveIndex = 4;
    const int blackPawnCaptureIndex = 5;
    const int blackPromotionMoveIndex = 6;
    const int blackPromotionCaptureIndex = 7;

    const int pawnDirZeroIndexVal = -1;
    const int pawnDirDiffIndex = 1;
}

namespace MOVE
{
    const int numOfPossibleTypesMoves = 6;
    const int checksIndex = 0;
    const int capturesIndex = 1;
    const int castleIndex = 2;
    const int enpassentIndex = 3;
    const int promotionIndex = 4;
    const int remainingMovesIndex = 5;
    const int nothingType = 69;
}

struct Move
{
    int type;
    std::pair<INDEX, INDEX> move;
    PIECE promotionTo = PIECE::QUEEN;

    Move (int t = MOVE::nothingType, std::pair<INDEX,INDEX> m = {{0,0},{0,0}}, PIECE p = PIECE::EMPTY)
    {
        type = t;
        move = m;
        promotionTo = p;
    }

    void print()
    {
        std::cout << "type : " << type << " | move : " << move.first.print() << "_" << move.second.print() << std::endl;
    }
};

namespace PIECE_VISION
{
    const int pawnVisionsIndex = 0;
    const int knightVisionsIndex = 1;
    const int bishopVisionsIndex = 2;
    const int rookVisionsIndex = 3;
    const int queenVisionsIndex = 4;
    const int kingVisionsIndex = 5;

    const std::map<PIECE, int> pieceVisionIndex = {{PIECE::PAWN, pawnVisionsIndex}, {PIECE::KNIGHT, knightVisionsIndex}, {PIECE::BISHOP, bishopVisionsIndex}, {PIECE::ROOK, rookVisionsIndex}, {PIECE::QUEEN, queenVisionsIndex}, {PIECE::KING, kingVisionsIndex}};
}

namespace UI
{
    const std::map<std::pair<PIECE, int>, char> pieceToChar = {{{PIECE::KING, COLOR::white}, 'K'}, {{PIECE::QUEEN, COLOR::white}, 'Q'}, {{PIECE::ROOK, COLOR::white}, 'R'}, {{PIECE::BISHOP, COLOR::white}, 'B'}, {{PIECE::KNIGHT, COLOR::white}, 'N'}, {{PIECE::PAWN, COLOR::white}, 'P'}, {{PIECE::KING, COLOR::black}, 'k'}, {{PIECE::QUEEN, COLOR::black}, 'q'}, {{PIECE::ROOK, COLOR::black}, 'r'}, {{PIECE::BISHOP, COLOR::black}, 'b'}, {{PIECE::KNIGHT, COLOR::black}, 'n'}, {{PIECE::PAWN, COLOR::black}, 'p'}, {{PIECE::EMPTY, COLOR::nothing}, '*'}};
}

namespace MATERIAL
{
    const int EMPTY = 0;
    const int PAWN = 1;
    const int KNIGHT = 3;
    const int BISHOP = 3;
    const int ROOK = 5;
    const int QUEEN = 9;
    const int KING = 1000;

    const std::map<PIECE, int> pieceMaterial = {{PIECE::EMPTY, EMPTY}, {PIECE::PAWN, PAWN}, {PIECE::KNIGHT, KNIGHT}, {PIECE::BISHOP, BISHOP}, {PIECE::ROOK, ROOK}, {PIECE::QUEEN, QUEEN}, {PIECE::KING, KING}};
}

namespace NOTATION
{
    const char check = '+';
    const char checkmate = '#';
    const char capture = 'x';
    const char promotion = '=';

    const std::map<char, PIECE> charToPiece = {{'N', PIECE::KNIGHT}, {'B', PIECE::BISHOP}, {'R', PIECE::ROOK}, {'Q', PIECE::QUEEN}, {'K', PIECE::KING}};
}

#endif // DEFINATION_H_INCLUDED
