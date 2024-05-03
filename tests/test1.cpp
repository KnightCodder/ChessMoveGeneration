#include "game.h"

void compilingPieceVision();
void checkPrecomiledpiecevision();

int main()
{
    compilingPieceVision();
    // checkPrecomiledpiecevision();

    Board a;
    a.playMove(a.notationsToIndex(""));
    a.printBoard();


    return 0;
}