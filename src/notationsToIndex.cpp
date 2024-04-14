#include <cctype>
#include "board.h"

Move Board::notationsToIndex(std::string move)
{
    INDEX from, to;
    PIECE pieceType = PIECE::PAWN;
    PIECE promotionPiece = PIECE::QUEEN;
    int type;
    int it = 0;
    if (move == "O-O")
    {
        from.file = 4;
        to.file = 6;
        int rank = 0;
        if (turn == TURN::black)
            rank = 7;
        from.rank = rank;
        to.rank = rank;

        return Move(MOVE::castleIndex, {from, to}, promotionPiece);
    }

    if (move == "O-O-O")
    {
        from.file = 4;
        to.file = 2;
        int rank = 0;
        if (turn == TURN::black)
            rank = 7;
        from.rank = rank;
        to.rank = rank;

        return Move(MOVE::castleIndex, {from, to}, promotionPiece);
    }

    if (std::isupper(move[it]))
    {
        pieceType = NOTATION::charToPiece.at(move[it]);
        it++;

        INDEX temp;

        if (std::isalpha(move[it]) && move[it] != NOTATION::capture)
        {
            temp.file = move[it] - 'a';
            it++;
        }
        if (std::isdigit(move[it]))
        {
            temp.rank = move[it] - '1';
            it++;
        }

        if (move[it] == NOTATION::capture)
        {
            from = temp;
            it++;
            to.file = move[it] - 'a';
            it++;
            to.rank = move[it] - '1';
        }
        else if (std::isalpha(move[it]))
        {
            from = temp;
            to.file = move[it] - 'a';
            it++;
            to.rank = move[it] - '1';
        }
        else
        {
            to = temp;
        }
    }
    else
    {
        from.file = move[it] - 'a';
        it++;

        if (move[it] == NOTATION::capture)
        {
            it++;
            to.file = move[it] - 'a';
            it++;
            to.rank = move[it] - '1';
            it++;
        }
        else
        {
            to.file = from.file;
            to.rank = move[it] - '1';
            it++;
        }

        if (move[it] == NOTATION::promotion)
        {
            it++;
            promotionPiece = NOTATION::charToPiece.at(move[it]);
        }
    }

    for (auto x : boardIndex(to)->watchers)
    {
        if (boardIndex(x.first)->pieceType == pieceType && boardIndex(x.first)->color == turn && (from.file == SQUARE::empty || from.file == x.first.file) && (from.rank == SQUARE::empty || from.rank == x.first.rank))
        {
            from = x.first;

            for (auto y : boardIndex(from)->moves.at(x.second))
            {
                if (y.second == to)
                {
                    type = y.first;
                    break;
                }
            }

            break;
        }
    }

    return Move(type, {from, to}, promotionPiece);
}