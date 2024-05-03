#include "board.h"

void Board::playMove(Move moveData)
{
    if (moveData.type == MOVE::checksIndex)
    {
        std::cout << "ERROR : capturing king : " << moveData.move.first.print() << "_" << moveData.move.second.print() << std::endl;
        return;
    }

    else if (moveData.type == MOVE::remainingMovesIndex || moveData.type == MOVE::capturesIndex)
    {
        update(moveData.move.first, moveData.move.second);
    }

    else if (moveData.type == MOVE::enpassentIndex)
    {
        INDEX index(moveData.move.first.rank, moveData.move.second.file);

        update(moveData.move.first, index);
        update(index, moveData.move.second, true);
    }

    else if (moveData.type == MOVE::castleIndex)
    {
        update(moveData.move.first, moveData.move.second);

        if (moveData.move.second.file == 6)
            update(INDEX(moveData.move.first.rank, 7), INDEX(moveData.move.first.rank, 5), true);
        else if (moveData.move.second.file == 2)
            update(INDEX(moveData.move.first.rank, 0), INDEX(moveData.move.first.rank, 3), true);
    }

    else if (moveData.type == MOVE::promotionIndex)
    {
        boardIndex(moveData.move.first)->pieceType = moveData.promotionTo;
        materialBalance += turn * (MATERIAL::pieceMaterial.at(moveData.promotionTo) - 1);
        update(moveData.move.first, moveData.move.second);
    }

    else
    {
        std::cout << "ERROR : Invalid Type :- " << moveData.type << std::endl;
    }
}
