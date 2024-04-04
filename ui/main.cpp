#include "board.h"
// #include"defination.h"

void compilingPieceVision();

int main()
{
    compilingPieceVision();

    Board a;

    while (true)
    {
        totalMoves moves = a.moveGeneration();
        a.printBoard();
        for (int i = 0; i < 6; i++)
        {
            for (auto j : moves[i])
            {
                std::cout << "type : " << i << " | " << j.first.print() << "_" << j.second.print() << std::endl;
            }
        }
        // a.temp();

        std::string from, to;
        int type;
        std::cout << "\n\nenter move : ";
        std::cin >> type >> from >> to;

        INDEX _from,_to;
        _from.strToIndex(from);
        _to.strToIndex(to);

        a.playMove(type, {_from, _to});
    }

    std::cout << "end" << std::endl;
    return 0;
}
