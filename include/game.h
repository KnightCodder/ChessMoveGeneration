#ifndef GAME_H
#define GAME_H

#include "position.h"

class Game
{
public:
    std::vector<Position> game;

    Game(std::string PGN)
    {
        std::string pgncopy = "";
        Board currentBoard;

        for (unsigned int i = 0; i < PGN.length(); i++)
        {
            // std::cout << "what" << std::endl;
            if (PGN[i] == ' ')
            {
                i++;
                while (PGN[i] != ' ')
                {
                    // std::cout << "what the fuck" << std::endl;
                    if (PGN[i] == '!' || PGN[i] == '?')
                    {
                        i++;
                        continue;
                    }
                    if (PGN[i] == ']')
                    {
                        i += 10;
                        break;
                    }
                    pgncopy.push_back(PGN[i]);
                    i++;
                }
                pgncopy.push_back(' ');
                i += 8;
            }
        }

        // std::cout << pgncopy << std::endl;

        std::istringstream iss(pgncopy);

        std::string m;
        double e;
        int moveNum = 0;
        bool whiteMove = true;

        while (iss >> m)
        {
            iss >> e;
            Move moveData = currentBoard.notationsToIndex(m);
            currentBoard.playMove(moveData);
            if (whiteMove)
                moveNum++;

            game.push_back(Position(currentBoard, moveNum, e, moveData.move));

            whiteMove = !whiteMove;
        }
    }

    void print()
    {
        std::cout << "\n\n------------------------------------------------------------------\n";
        for (auto x : game)
        {
            x.print();
            std::cout << "\n------------------------------------------------------------------\n";
        }
    }
};

#endif