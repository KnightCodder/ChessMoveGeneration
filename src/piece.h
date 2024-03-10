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
    std::array<std::vector<Piece *>, 8> vision = {}; // points to board
    std::set<Piece *> relatives = {};                // points to piece which are seeing it
    std::array<std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>, 6> moves = {};

    Piece()
    {
    }

    ~Piece()
    {
    }

    void delete_relative(Piece *address)
    {
        auto it = relatives.find(address);

        if (it != relatives.end())
            relatives.erase(it);
    }
    
};

#endif