#include "board.h"
#include <chrono>
#include <algorithm>

void compilingPieceVision();


int main()
{
    compilingPieceVision();

    Board a("rn1q1rk1/1p1Pbpp1/p1p1pn2/5b1p/3P4/1N3NP1/PP2PPBP/R1BQR1K1 b - - 0 13");

    std::pair<std::pair<int,std::pair<INDEX, INDEX>>,PIECE> move = a.notationsToIndex("Nfxd7");
    std::cout << "type : " << move.first.first << " | " << move.first.second.first.print() << " " << move.first.second.second.print() << " | piece : " << UI::pieceToChar.at({move.second, a.turn}) << std::endl;
    // std::cout << move.first.file << move.first.rank << " " << move.second.print() << std::endl;

    return 0;
}
