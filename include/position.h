// this is created to convert pgn with evaluation to convert into Board and evaluation pair
// currently it is not too flexible

#ifndef POSITION_H
#define POSITION_H

#include "board.h"

struct Position
{
    Board board;
    int moveNum;
    double eval = 0;
    std::pair<INDEX, INDEX> move;

    Position(Board b = Board(BOARD::defaultFen), int mn = 1, double e = 0, std::pair<INDEX, INDEX> m = {{1,1},{1,1}})
    {
        board = b;
        moveNum = mn;
        eval = e;
        move = m;
    }

    void print()
    {
        board.printBoard();
        std::cout << "move number : " << moveNum << "\neval : " << eval << "\nmove : " << move.first.print() << "_" << move.second.print() << std::endl;
    }

    bool operator==(const Position &other) const
    {
        return board == other.board;
    }

    bool operator<(const Position &other) const
    {
        return board < other.board;
    }

    std::string toCSV();
};

#endif