#include "board.h"
#include <chrono>
#include <algorithm>

void compilingPieceVision();

const int maxDepth = 2;
const int illegal = 6969;
const int winBlack = -30;
const int winWhite = -30;

unsigned long long int branches = 0, positions = 0;
std::vector<Board> TFRLT;

int negamax(Board position, int depth, int alpha, int beta)
{
    // std::cout << "part 0" << std::endl;
    branches++;
    TFRLT.push_back(position);
    totalMoves nextMoves = position.moveGeneration();
    // std::cout << "part 1" << std::endl;

    if (position.illegal)
        return illegal;

    else if (position.fiftyMoves >= 100)
        return -0;
    else if (std::count(TFRLT.begin(), TFRLT.end(), position) >= 3)
        return -0;
    else if (depth == 0)
    {
        positions++;
        // std::cout << "how the hell i am here" << std::endl;
        return (position.turn * position.materialBalance);
    }
    // std::cout << "part 2" << std::endl;

    int bestValue = winBlack;
    bool mate = true;

    Board temp = position;
    bool _break = false;

    // std::cout << "part 3" << std::endl;
    for (int i = 0; i < 6; i++)
    {
        for (auto j : nextMoves[i])
        {
            position = temp;
            position.playMove(i,j);

            int value = -negamax(position, depth - 1, -beta, -alpha);

            // std::cout << "finally made it : " << value << std::endl;
            TFRLT.pop_back();

            if (maxDepth == depth)
                std::cout << j.first.print() << j.second.print() << " : " << value << std::endl;

            if (value != illegal && value != -illegal)
            {
                mate = false;
                bestValue = std::max(bestValue, value);
                alpha = std::max(alpha, value);
                if (alpha >= beta)
                {
                    std::cout << "about to break" << std::endl;
                    break;
                }
            }
        }
        if (_break)
            break;
    }
    // std::cout << "part 4" << std::endl;

    if (mate)
    {
        if (temp.checks)
            return winBlack;
        return -0;
    }

    // std::cout << "complete" << std::endl;
    return bestValue;
}

int main()
{
    compilingPieceVision();

    Board a;

    auto start = std::chrono::high_resolution_clock::now();
    int bestScore = negamax(a, maxDepth, winBlack, winWhite);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    double elapsedTime = duration.count();

    std::cout << "Best score: " << bestScore << std::endl;
    std::cout << "Elapsed time: " << elapsedTime << " seconds" << std::endl;
    std::cout << "analyzed positions : " << positions << std::endl;
    std::cout << "branches : " << branches << std::endl;

    std::cout << "end" << std::endl;
    return 0;
}
