#include "board.h"

void Board::playMove(int type, std::pair<INDEX,INDEX> move, PIECE promotionTo)
{
    if (type == MOVE::checksIndex)
    {
        std::cout << "ERROR : capturing king : " << move.first.print() << "_" << move.second.print() << std::endl;
        return;
    }

    else if (type == MOVE::remainingMovesIndex || type == MOVE::capturesIndex)
    {
        update(move.first, move.second);
    }

    else if (type == MOVE::enpassentIndex)
    {
        INDEX index(move.first.rank, move.second.file);

        update(move.first, index);
        update(index, move.second, true);
    }

    else if (type == MOVE::castleIndex)
    {
        update(move.first, move.second);

        if (move.second.file == 6)
            update(INDEX(move.first.rank, 7), INDEX(move.first.rank, 5), true);
        else if (move.second.file == 2)
            update(INDEX(move.first.rank, 0), INDEX(move.first.rank, 3), true);
    }

    else if (type == MOVE::promotionIndex)
    {
        boardIndex(move.first)->pieceType = promotionTo;
        materialBalance += turn * (MATERIAL::pieceMaterial.at(promotionTo) - 1);
        update(move.first, move.second);
    }

    else
    {
        std::cout << "ERROR : Invalid Type" << std::endl;
    }
}
