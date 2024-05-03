#include "game.h"

void compilingPieceVision();
void checkPrecomiledpiecevision();

int main()
{
    compilingPieceVision();

    Board a("r4rk1/pp1n1pp1/2p1pn1P/6R1/2PP4/1q1BKN2/1P3Q2/7R b - - 0 22");
    // Board a;

    while(true)
    {
        a.printBoard();
        std::cout << "\n---------------------------------------------\n";

        std::string move;
        std::cout << "enter move : ";
        std::cin >> move;
        
        a.playMove(a.notationsToIndex(move));
        a.moveGeneration();
    }

// d4 Nf6 Bg5 Ne4 Bh4 g5 f3 gxh4 fxe4 c5 e3 Bh6 Nc3 Bxe3 Bc4 cxd4 Nd5 b5 Nxe3 dxe3 Bxf7+ Kxf7 Qh5+ Kg7 Qg5+ Kf7 Nh3 Qg8 Qd5+ e6 O-O+ Ke7 Qxa8 Nc6 Rae1 Qg7 Rxe3 Rg8 Nf4 Qd4 Re1 Qxb2 Ne2 Qxc2 Rc1 Qd2 Kf2 Nd4 Qxa7 Rf8+ Kg1 Qxe3+ Kh1 Qxc1+

    return 0;
}