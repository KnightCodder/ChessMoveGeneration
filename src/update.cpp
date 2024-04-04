#include "board.h"

void Board::update(INDEX from, INDEX to, bool halfMove)
{
    PIECE fromPiece = boardIndex(from)->pieceType;
    PIECE toPiece = boardIndex(to)->pieceType;
    int fromColor = boardIndex(from)->color;
    int toColor = boardIndex(to)->color;

    // deleting self from watching
    {
        auto x = boardIndex(from)->watchingSquare;
        for (auto i : x)
        {
            for (auto j : i.second)
                boardIndex(j)->watchers.erase(from);
        }
        boardIndex(from)->watchingSquare = {};
    }

    // deleting watching and watcher of watching piece of captured piece
    {
        auto x = boardIndex(to)->watchingSquare;
        for (auto i : x)
        {
            for (auto j : i.second)
                boardIndex(j)->watchers.erase(to);
        }
        boardIndex(to)->watchingSquare = {};
    }

    // move
    {
        boardIndex(to)->isEmpty = boardIndex(from)->isEmpty;
        boardIndex(to)->color = boardIndex(from)->color;
        boardIndex(to)->pieceType = boardIndex(from)->pieceType;

        boardIndex(from)->isEmpty = true;
        boardIndex(from)->color = COLOR::nothing;
        boardIndex(from)->pieceType = PIECE::EMPTY;
    }

    // moves at new location
    {
        boardIndex(to)->moves = pieceMoveGeneration({to.rank, to.file});
    }

    // previous watcher update
    {
        auto x = boardIndex(from)->watchers;
        for (auto i : x)
        // for (auto i : boardIndex(from)->watchers)
        {
            boardIndex(i.first)->moves[i.second] = pieceMoveGenerationDirection(i.first, i.second);
        }
    }

    // current watcher update
    {
        auto x = boardIndex(to)->watchers;
        // for (auto i : boardIndex(to)->watchers)
        for (auto i : x)
        {
            boardIndex(i.first)->moves[i.second] = pieceMoveGenerationDirection(i.first, i.second);
        }
    }

    if (halfMove)
        return;

    // castle
    {
        if (from == INDEX(0, 4) || from == INDEX(0, 7) || from == INDEX(0, 4) || to == INDEX(0, 7))
            castle[BOARD::whiteKingSideCastleIndex] = false;
        if (from == INDEX(0, 4) || from == INDEX(0, 0) || from == INDEX(0, 4) || to == INDEX(0, 0))
            castle[BOARD::whiteQueenSideCastleIndex] = false;
        if (from == INDEX(7, 4) || from == INDEX(7, 7) || from == INDEX(7, 4) || to == INDEX(7, 7))
            castle[BOARD::blackKingSideCastleIndex] = false;
        if (from == INDEX(7, 4) || from == INDEX(7, 0) || from == INDEX(7, 4) || to == INDEX(7, 0))
            castle[BOARD::blackQueenSideCastleIndex] = false;
    }

    // enpassent
    {
        enpassent = SQUARE::empty;
        if (fromPiece == PIECE::PAWN && ((from.rank == 1 && to.rank == 3) || (from.rank == 6 && to.rank == 4)))
        {
            if (((to.file > 0 && boardIndex(INDEX(to.rank, to.file - 1))->pieceType == PIECE::PAWN) || (to.file < 7 && boardIndex(INDEX(to.rank, to.file + 1))->pieceType == PIECE::PAWN)) && (fromColor * boardIndex(INDEX(to.rank, to.file - 1))->color < 0 || fromColor * boardIndex(INDEX(to.rank, to.file + 1))->color < 0))
            {
                enpassent = INDEX((from.rank + to.rank) / 2, to.file);
            }
        }
    }

    // fifty moves
    {
        fiftyMoves++;
        if(fromPiece == PIECE::PAWN)
            fiftyMoves = 0;
        if(toPiece != PIECE::EMPTY)
            fiftyMoves = 0;
    }

    // material Balance
    {
        materialBalance -= toColor * MATERIAL::pieceMaterial.at(toPiece);
    }

    turn *= -1;

}
