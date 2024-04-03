#include "../src/board.h"

int main()
{
    // Board a;
    // a.printBoard();
    for (int i = 0; i < 10; i++)
    {
        INDEX a;
        a.setIndex(1,4);
        std::cout << a.print() << std::endl;
    }
    

    return 0;
}