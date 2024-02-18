#include "../src/Board/board.h"

int main()
{
    Board myboard(default_fen);
    myboard.printBoard();
    int index[] = {3, 3};
    myboard.knight_vision(index);
}