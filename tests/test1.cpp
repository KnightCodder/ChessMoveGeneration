#include "board.h"

int main()
{
    Board myboard("rnbq1bnr/ppp1kppp/4p3/3p4/2PP4/8/PP1KPPPP/RNBQ1BNR w - - 2 4");
    // myboard.printBoard();

    // e5
    int from[] = {1, 3};
    int to[] = {2, 3};

    myboard.update(from, to, false);

    // from[0] = 7;
    // from[1] = 7;
    // to[0] = 7;
    // to[1] = 5;

    // myboard.update(from, to, true);

    myboard.printBoard();

    return 0;
}