#ifndef PIECE_H
#define PIECE_H

#include "defination.h"

struct Piece
{
    bool isEmpty = true;
    int color = COLOR::nothing;
    PIECE pieceType = PIECE::EMPTY;
    INDEX index;
    movesOfaPiece moves;
    watch watchers = {};
    watching watchingSquare = {};
};

#endif