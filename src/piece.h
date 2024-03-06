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
    std::array<std::vector<Piece *>, 8>vision; // points to board

    Piece(){

    }

    ~Piece()
    {

    }
};

#endif