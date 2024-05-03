#include "game.h"

void compilingPieceVision();
void checkPrecomiledpiecevision();

int main()
{
    compilingPieceVision();
    // checkPrecomiledpiecevision();

    Board a("3r2k1/1p1R1rq1/pN5p/5pp1/2Q5/7P/PP3PP1/4R1K1 b - - 0 28");
    Move wtf = a.notationsToIndex("Rxd7");

    // wtf.print();

    // a.playMove(wtf);
    // a.moveGeneration();

    // a.printBoard();


    return 0;
}