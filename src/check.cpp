#include "board.h"

bool Board::isCheck(int color)
{
    if (color == black_turn)
    {
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 8; j++)
            {
                for(auto k : black_king_check_vision[i][j])
                {
                    
                }
            }
        }
    }
    return true;
}