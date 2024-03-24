#include "board.h"

int *moveToIndex(std::string move)
{
    int *arr = new int[2];

    arr[0] = move[1] - '1';
    arr[1] = move[0] - 'a';

    return arr;
}

int main()
{
    Board myboard(default_fen);
    myboard.printBoard();

    // https://lichess.org/2koHXWh0

    myboard.update(moveToIndex("d2"), moveToIndex("d4"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("g8"), moveToIndex("f6"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("c2"), moveToIndex("c4"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("e7"), moveToIndex("e6"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("g2"), moveToIndex("g3"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("b7"), moveToIndex("b6"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("f1"), moveToIndex("g2"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("c7"), moveToIndex("c6"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("g1"), moveToIndex("f3"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("c8"), moveToIndex("a6"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("b2"), moveToIndex("b3"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("f8"), moveToIndex("b4"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("c1"), moveToIndex("d2"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("d8"), moveToIndex("e7"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("e1"), moveToIndex("g1"));
     myboard.update(moveToIndex("h1"), moveToIndex("f1"), true);
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("b4"), moveToIndex("d2"));
    myboard.printBoard();
    std::cout<<std::endl;

    myboard.update(moveToIndex("b1"), moveToIndex("d2"));
    myboard.printBoard();
    std::cout<<std::endl;

    // myboard.update(moveToIndex("d7"), moveToIndex("d5"));
    // myboard.printBoard();
    // std::cout<<std::endl;
    
    // myboard.update(moveToIndex("f3"), moveToIndex("e5"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("e8"), moveToIndex("g8"));
    //  myboard.update(moveToIndex("h8"), moveToIndex("f8"), true);
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("h2"), moveToIndex("h4"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("h7"), moveToIndex("h6"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("h4"), moveToIndex("h5"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("g7"), moveToIndex("g5"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("h5"), moveToIndex("g5"), true);
    // myboard.update(moveToIndex("g5"), moveToIndex("g6"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("f8"), moveToIndex("e8"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("g6"), moveToIndex("f7"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("g8"), moveToIndex("h8"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("e5"), moveToIndex("g6"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("h8"), moveToIndex("g7"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("g6"), moveToIndex("f8"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.update(moveToIndex("g7"), moveToIndex("f8"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    // myboard.temp_promote(PieceType::QUEEN, moveToIndex("f7"));
    // myboard.update(moveToIndex("f7"), moveToIndex("e8"));
    // myboard.printBoard();
    // std::cout<<std::endl;

    return 0;
}
