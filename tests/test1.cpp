#include "board.h"
// #include"defination.h"

void compilingPieceVision();

int main()
{
    compilingPieceVision();

    Board a(BOARD::defaultFen);
    a.printBoard();

    // a.update(BOARD::squareNameToIndex("h2"),BOARD::squareNameToIndex("h3"));


    // a.update(BOARD::squareNameToIndex("e7"),BOARD::squareNameToIndex("e5"));
    // a.temp(BOARD::squareNameToIndex("c4"));

    // a.printBoard();

    // totalMoves moves = a.moveGeneration();

    // for (int type = 0; type < MOVE::numOfPossibleTypesMoves; type++)
    // {
    //     for (auto i : moves[type])
    //     {
    //         std::cout << "type : " << type << " | move : " << BOARD::indexToSquareName(i.first) << "_" << BOARD::indexToSquareName(i.second) << std::endl;
    //     }
    // }

    // movesOfaPiece moves = a.pieceMoveGeneration(BOARD::squareNameToIndex("f6"));
    // for (auto i : moves)
    // {
    //     for (auto j : i.second)
    //     {
    //         std::cout << i.first[0] << "_" << i.first[1] << "  |  type : " << j.first << " | move : " << BOARD::indexToSquareName(j.second) << std::endl;
    //     }
    //     std::cout << std::endl;
    // }


    // movesInSingleDirection moves = a.pieceMoveGenerationDirection(BOARD::squareNameToIndex("d7"), {-1, 3});

    // for (auto i : moves)
    // {
    //     std::cout << "type : " << i.first << " | move : " << BOARD::indexToSquareName(i.second) << std::endl;
    // }

    std::cout << "end" << std::endl;
    return 0;
}