#include "board.h"

void compilingPieceVision();

int main()
{
    compilingPieceVision();

    Board myBoard(BOARD::defaultFen);

    while (myBoard.status == GameStatus::STILL_GOING)
    {
        std::cout << "\n-------------------------------------------------------" << std::endl;
        myBoard.printBoard();
        std::string move;
        std::cout << "\nenter a move : ";
        std::cin >> move;
        myBoard.playMove(myBoard.notationsToIndex(move));
    }

    return 0;
}