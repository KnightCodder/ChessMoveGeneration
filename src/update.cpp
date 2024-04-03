#include "board.h"

void Board::update(INDEX from, INDEX to)
{
    // PIECE piece_from = boardIndex(from)->pieceType;
    // PIECE piece_to = boardIndex(to)->pieceType;

    std::cout << "updating 0" << std::endl;

    // deleting self from watching
    {
        for (auto i : boardIndex(from)->watchingSquare)
        {
            for (auto j : i.second)
                boardIndex(j)->watchers.erase(from);
        }
        boardIndex(from)->watchingSquare = {};
    }

    std::cout << "updating 1" << std::endl;
    // move
    {
        boardIndex(to)->isEmpty = boardIndex(from)->isEmpty;
        boardIndex(to)->color = boardIndex(from)->color;
        boardIndex(to)->pieceType = boardIndex(from)->pieceType;

        boardIndex(from)->isEmpty = true;
        boardIndex(from)->color = COLOR::nothing;
        boardIndex(from)->pieceType = PIECE::EMPTY;
    }

    std::cout << "updating 2" << std::endl;
    // moves at new location
    {
        boardIndex(to)->moves = pieceMoveGeneration({to.rank, to.file});
    }
    std::cout << "updating 3" << std::endl;

    // previous watcher update
    {
        for (auto i : boardIndex(from)->watchers)
        {
            boardIndex(i.first)->moves[i.second] = pieceMoveGenerationDirection(i.first, i.second);
        }
    }

    std::cout << "updating 4" << std::endl;
    // current watcher update
    {
        for (auto i : boardIndex(to)->watchers)
        {
            // std::cout << i.first[0] << "_" << i.first[1] << " | " << i.second[0] << "_" << i.second[1] << std::endl;
            // std::cout << BOARD::indexToSquareName(i.first) << " | " << i.second[0] << "_" << i.second[1] << std::endl;

            // for (auto j : pieceMoveGenerationDirection(i.first, i.second))
            // {
            //     std::cout << "Hello World" << std::endl;
            //     std::cout << "type : " << j.first << " | move : " << BOARD::indexToSquareName(j.second) << std::endl;
            // }

            boardIndex(i.first)->moves.insert({i.second, pieceMoveGenerationDirection(i.first, i.second)});

        }
    }

    std::cout << "updating 5" << std::endl;
    {
        turn *= -1;
        fiftyMoves++;
    }
    std::cout << "updating complete" << std::endl;
}
