// src/PieceVision/pieceVision.cpp
#include "../Board/board.h"

Piece*** Board::bishop_vision(int index[])
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int som[][2] = {{1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

    int rank, file;

    for (int i = 0; i < 8; i += 2)
    {
        rank = index[0];
        file = index[1];
        for (int j = 0; j < 7; j++)
        {
            rank += som[i / 2][0];
            file += som[i / 2][1];

            if (rank < 0 || rank > 7 || file < 0 || file > 7)
                break;

            array[i][j] = &board[rank][file];
            std::cout << "i : " << i << "  j : " << j << "  rank : " << rank << "  file : " << file << std::endl;
        }
    }

    return array;
}

Piece*** Board::rook_vision(int index[])
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int som[][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int rank, file;

    for (int i = 1; i < 8; i += 2)
    {
        rank = index[0];
        file = index[1];
        for (int j = 0; j < 7; j++)
        {
            rank += som[(i - 1) / 2][0];
            file += som[(i - 1) / 2][1];

            if (rank < 0 || rank > 7 || file < 0 || file > 7)
                break;

            array[i][j] = &board[rank][file];
            std::cout << "i : " << i << "  j : " << j << "  rank : " << rank << "  file : " << file << std::endl;
        }
    }

    return array;
}

Piece*** Board::queen_vision(int index[])
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int som[][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    int rank, file;

    for (int i = 0; i < 8; i++)
    {
        rank = index[0];
        file = index[1];
        for (int j = 0; j < 7; j++)
        {
            rank += som[i][0];
            file += som[i][1];

            if (rank < 0 || rank > 7 || file < 0 || file > 7)
                break;

            array[i][j] = &board[rank][file];
            std::cout << "i : " << i << "  j : " << j << "  rank : " << rank << "  file : " << file << std::endl;
        }
    }

    return array;
}

Piece*** Board::king_vision(int index[])
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int som[][2] = {{1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

    int rank, file;

    for (int i = 0; i < 8; i++)
    {
        rank = index[0];
        file = index[1];

        rank += som[i][0];
        file += som[i][1];

        if (rank < 0 || rank > 7 || file < 0 || file > 7)
            break;

        array[i][0] = &board[rank][file];
        std::cout << "i : " << i << "  j : " << 0 << "  rank : " << rank << "  file : " << file << std::endl;
    }

    return array;
}

Piece*** Board::knight_vision(int index[])
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int som[][2] = {{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};

    int rank, file;

    for (int i = 0; i < 8; i++)
    {
        rank = index[0];
        file = index[1];

        rank += som[i][0];
        file += som[i][1];

        if (rank < 0 || rank > 7 || file < 0 || file > 7)
            break;

        array[i][0] = &board[rank][file];
        std::cout << "i : " << i << "  j : " << 0 << "  rank : " << rank << "  file : " << file << std::endl;
    }

    return array;
}

Piece*** Board::pawn_vision(int index[], int color)
{
    Piece ***array = new Piece **[8];

    for (int i = 0; i < 8; i++)
    {
        array[i] = new Piece *[7];
        for (int j = 0; j < 7; j++)
            array[i][j] = nullptr; // Initialize each pointer with nullptr
    }

    int rank = index[0];
    int file = index[1];

    if (rank == 1 && color == white_turn)
        array[0][1] = &board[rank + 2][file];
    if (rank == 6 && color == black_turn)
        array[0][1] = &board[rank - 2][file];
    if (rank < 8 && rank > 0 && (rank != 6 || color == black_turn) && (rank != 1 || color == white_turn))
    {
        array[0][0] = &board[rank + color][file];
        if (file < 7)
            array[1][0] = &board[rank + color][file + 1];
        if (file > 0)
            array[1][1] = &board[rank + color][file - 1];
    }
    else
    {
        array[2][0] = &board[rank + color][file];
        if (file < 7)
            array[3][0] = &board[rank + color][file + 1];
        if (file > 0)
            array[3][1] = &board[rank + color][file - 1];
    }
}

Piece*** Board::piece_vision(int index[])
{
    int rank = index[0];
    int file = index[1];
    PieceType pieceType = board[rank][file].piece_type;

    if (board[rank][file].isEmpty)
        return nullptr;
    else if (pieceType == PieceType::PAWN)
        return pawn_vision(index, board[rank][file].color);
    else if (pieceType == PieceType::KNIGHT)
        return knight_vision(index);
    else if (pieceType == PieceType::BISHOP)
        return bishop_vision(index);
    else if (pieceType == PieceType::ROOK)
        return rook_vision(index);
    else if (pieceType == PieceType::QUEEN)
        return queen_vision(index);
    else if (pieceType == PieceType::KING)
        return king_vision(index);
    else
        std::cout << "error in Piece*** Board::piece_vision" << std::endl;
}
