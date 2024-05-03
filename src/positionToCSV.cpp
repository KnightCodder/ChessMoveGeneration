#include "position.h"
#include <sstream>

std::string Position::toCSV()
{
    std::stringstream data;
    board.moveGeneration();

    data << moveNum << ',' << board.turn << ',' << board.checks << ',' << board.castle[BOARD::whiteKingSideCastleIndex] << ',' << board.castle[BOARD::whiteQueenSideCastleIndex] << ',' << board.castle[BOARD::blackKingSideCastleIndex] << ',' << board.castle[BOARD::blackQueenSideCastleIndex] << ',' << board.fiftyMoves << ',' << board.materialBalance << ',' << eval;


    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            Piece *piece = board.boardIndex({rank, file});

            int WWatchers = 0, BWatchers = 0, EWatching = 0, WWatching = 0, BWatching = 0, KWatching = 0;

            for (auto x : piece->watchers)
            {
                if (board.boardIndex(x.first)->color == COLOR::white)
                    WWatchers++;
                else if (board.boardIndex(x.first)->color == COLOR::black)
                    BWatchers++;
                else
                    std::cout << "error in watchers" << std::endl;
            }

            for (auto x : piece->watchingSquare)
            {
                for (auto y : x.second)
                {
                    if (board.boardIndex(y)->color == board.turn && board.boardIndex(y)->pieceType == PIECE::KING)
                        KWatching++;
                    else if (board.boardIndex(y)->color == COLOR::white)
                        WWatching++;
                    else if (board.boardIndex(y)->color == COLOR::black)
                        BWatching++;
                    else if (board.boardIndex(y)->color == COLOR::nothing)
                        EWatching++;
                    else
                        std::cout << "error in watching square" << std::endl;
                }
            }

            data << ',' << (piece->pieceType == PIECE::PAWN) << ',' << (piece->pieceType == PIECE::KNIGHT) << ',' << (piece->pieceType == PIECE::BISHOP || piece->pieceType == PIECE::QUEEN) << ',' << (piece->pieceType == PIECE::ROOK || piece->pieceType == PIECE::QUEEN) << ',' << (piece->pieceType == PIECE::KING) << ',' << piece->color << ',' << WWatchers << ',' << BWatchers << ',' << EWatching << ',' << WWatching << ',' << BWatching << ',' << KWatching;
        }
    }

    return data.str();
}