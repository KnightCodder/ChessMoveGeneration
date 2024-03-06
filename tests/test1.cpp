#include "board.h"

int main()
{
    Board myboard(default_fen);
    myboard.printBoard();

    int from[] = {0, 1};
    int to[] = {2, 2};

    myboard.update(from, to);
    myboard.printBoard();

    return 0;
}