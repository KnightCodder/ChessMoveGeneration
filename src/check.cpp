#include "board.h"

bool Board::Check()
{
    for (int rank = 0; rank < 8; rank++)
    {
        for (int file = 0; file < 8; file++)
        {
            if (board[rank][file].piece_type == PieceType::KING)
            {
                for (auto j : board[rank][file].relatives)
                {
                    if (j->color == -board[rank][file].color)
                    {
                        if (board[rank][file].color == turn)
                            isCheck = true;
                        else
                            illegal = true;
                    }
                }
            }
        }
    }

    return true;
}