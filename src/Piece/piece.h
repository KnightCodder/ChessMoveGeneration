// src/Piece/piece.h
#ifndef PIECE_H
#define PIECE_H

enum class PieceType
{
    EMPTY,
    PAWN,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

struct Piece
{
    bool isEmpty = true;
    int color = 0;
    PieceType piece_type = PieceType::EMPTY;
    int index = -1;
    Piece ***vision = nullptr; // points to board

    Piece() : vision(new Piece**[8]) {
        for (int i = 0; i < 8; i++)
            vision[i] = new Piece*[7];
    }

    ~Piece()
    {
        for (int i = 0; i < 8; i++)
            delete [] vision[i];
        delete [] vision;
    }
};

#endif