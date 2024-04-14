#include "game.h"

void compilingPieceVision();

int main()
{
    compilingPieceVision();

    // Board myBoard(BOARD::defaultFen);

    // while (myBoard.status == GameStatus::STILL_GOING)
    // {
    //     std::cout << "\n-------------------------------------------------------" << std::endl;
    //     myBoard.printBoard();
    //     std::string move;
    //     std::cout << "\nenter a move : ";
    //     std::cin >> move;
    //     myBoard.playMove(myBoard.notationsToIndex(move));
    // }

    std::string pgn = "1. d4 { [%eval 0.13] [%clk 0:02:00] } 1... d5 { [%eval 0.27] [%clk 0:02:00] } 2. e3 { [%eval 0.11] [%clk 0:01:59] } 2... e6 { [%eval 0.06] [%clk 0:02:00] } 3. Nc3 { [%eval -0.21] [%clk 0:01:59] } 3... Nf6 { [%eval -0.2] [%clk 0:02:00] } 4. Nf3 { [%eval -0.26] [%clk 0:01:59] } 4... c5 { [%eval -0.21] [%clk 0:02:00] } 5. Be2 { [%eval -0.31] [%clk 0:02:00] } 5... Nc6 { [%eval -0.34] [%clk 0:02:00] } 6. b3 { [%eval -0.51] [%clk 0:02:00] } 6... cxd4 { [%eval -0.63] [%clk 0:01:56] } 7. Nxd4 { [%eval -0.48] [%clk 0:01:55] } 7... Nxd4 { [%eval -0.31] [%clk 0:01:48] } 8. exd4 { [%eval -0.22] [%clk 0:01:55] } 8... Bb4 { [%eval -0.09] [%clk 0:01:43] } 9. Bd2 { [%eval -0.21] [%clk 0:01:54] } 9... Qc7 { [%eval 0.09] [%clk 0:01:41] } 10. Nb1 { [%eval -0.31] [%clk 0:01:48] } 10... Bxd2+ { [%eval -0.15] [%clk 0:01:30] } 11. Qxd2 { [%eval -0.13] [%clk 0:01:44] } 11... O-O { [%eval -0.06] [%clk 0:01:30] } 12. O-O { [%eval -0.3] [%clk 0:01:43] } 12... a6 { [%eval -0.04] [%clk 0:01:26] } 13. c4 { [%eval 0.0] [%clk 0:01:38] } 13... Rd8 { [%eval 0.0] [%clk 0:01:23] } 14. c5 { [%eval -0.1] [%clk 0:01:37] } 14... b6 { [%eval 0.08] [%clk 0:01:14] } 15. b4 { [%eval 0.18] [%clk 0:01:37] } 15... bxc5 { [%eval 0.06] [%clk 0:01:02] } 16. bxc5 { [%eval 0.01] [%clk 0:01:36] } 16... Ne4 { [%eval 0.07] [%clk 0:00:58] } 17. Qc2 { [%eval -0.17] [%clk 0:01:28] } 17... Bd7 { [%eval 0.32] [%clk 0:00:42] } 18. Nc3 { [%eval 0.44] [%clk 0:01:23] } 18... Nxc3 { [%eval 0.45] [%clk 0:00:36] } 19. Qxc3 { [%eval 0.47] [%clk 0:01:21] } 19... Bb5 { [%eval 0.62] [%clk 0:00:35] } 20. Qf3 { [%eval 0.08] [%clk 0:01:16] } 20... Qa5 { [%eval 0.23] [%clk 0:00:23] } 21. Bxb5 { [%eval 0.11] [%clk 0:01:14] } 21... axb5 { [%eval 0.18] [%clk 0:00:22] } 22. Qe2 { [%eval 0.16] [%clk 0:01:10] } 22... Qb4 { [%eval 0.17] [%clk 0:00:15] } 23. Qd3? { [%eval -0.91] [%clk 0:01:02] } 23... Rab8? { [%eval 0.86] [%clk 0:00:15] } 24. h3?! { [%eval 0.25] [%clk 0:00:59] } 24... f6? { [%eval 1.49] [%clk 0:00:13] } 25. Rfb1? { [%eval 1.46] [%clk 0:00:58] } 25... Qc4? { [%eval 1.76] [%clk 0:00:12] } 26. Qe3? { [%eval 0.34] [%clk 0:00:51] } 26... Kf7? { [%eval 1.85] [%clk 0:00:08] } 27. Kh2? { [%eval 0.24] [%clk 0:00:50] } 27... b4?! { [%eval 1.0] [%clk 0:00:07] } 28. Rc1?! { [%eval 0.97] [%clk 0:00:44] } 28... Qb5?! { [%eval 1.26] [%clk 0:00:04] } 29. Rcb1?! { [%eval 0.96] [%clk 0:00:42] } 29... Qa4?! { [%eval 1.66] [%clk 0:00:03] } 30. Rb3?! { [%eval 1.57] [%clk 0:00:37] } 30... Rb5? { [%eval 2.61] [%clk 0:00:03] } 31. Qf3? { [%eval 2.21] [%clk 0:00:32] } 31... Rdb8? { [%eval 3.77] [%clk 0:00:02] } 32. Qh5+? { [%eval 3.15] [%clk 0:00:31] } 1-0";

    Game a(pgn);
    a.print();

    return 0;
}