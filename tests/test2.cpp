#include <iostream>
#include <string>
#include <vector>

struct Move {
    std::string whiteMove;
    std::string blackMove;
    std::string whiteEval;
    std::string blackEval;
};

std::vector<Move> parsePGN(const std::string& pgn) {
    std::vector<Move> moves;
    std::string delimiter = " ";
    size_t pos = 0;
    std::string token;
    std::string pgnCopy = pgn;

    // Remove header information if exists
    if (pgnCopy.find("[") != std::string::npos) {
        pos = pgnCopy.find("\n\n");
        if (pos != std::string::npos) {
            pgnCopy = pgnCopy.substr(pos + 2);
        }
    }

    // Parse moves
    while ((pos = pgnCopy.find(delimiter)) != std::string::npos) {
        token = pgnCopy.substr(0, pos);
        if (token.find(".") == std::string::npos) {
            Move move;
            size_t moveStart = token.find("{") == std::string::npos ? 0 : token.find("}") + 1;
            move.whiteMove = token.substr(moveStart, token.find("?") == std::string::npos ? token.size() - moveStart : token.find("?") - moveStart + 1);
            move.whiteEval = token.substr(token.find("[%eval ") + 7, token.find("]") - (token.find("[%eval ") + 7));
            token.erase(0, pos + delimiter.length());
            pos = token.find(delimiter);
            token = token.substr(pos + 1);
            size_t moveEnd = token.find("{") == std::string::npos ? token.size() : token.find("{");
            move.blackMove = token.substr(0, token.find("?") == std::string::npos ? moveEnd : token.find("?"));
            move.blackEval = token.substr(token.find("[%eval ") + 7, token.find("]") - (token.find("[%eval ") + 7));
            moves.push_back(move);
        }
        pgnCopy.erase(0, pos + delimiter.length());
    }
    return moves;
}

int main() {
    std::string pgn = "1. d4 { [%eval 0.13] [%clk 0:05:00] } 1... d5 { [%eval 0.27] [%clk 0:05:00] } 2. c4 { [%eval 0.0] [%clk 0:05:02] } 2... Nf6?! { [%eval 0.71] [%clk 0:04:58] } 3. cxd5?! { [%eval 0.4] [%clk 0:05:02] } 3... Qxd5?! { [%eval 0.83] [%clk 0:04:58] } 4. Nc3?! { [%eval 0.5] [%clk 0:05:02] } 4... Qa5?! { [%eval 0.91] [%clk 0:04:55] } 5. Bd2?! { [%eval 0.95] [%clk 0:05:02] } 5... c6?! { [%eval 1.54] [%clk 0:04:56] } 6. e4?! { [%eval 1.37] [%clk 0:05:01] } 6... Qb4? { [%eval 3.79] [%clk 0:04:57] } 7. Nf3? { [%eval 1.99] [%clk 0:04:37] } 7... Qxb2?? { [%eval 5.21] [%clk 0:04:55] } 8. Bc4?? { [%eval 2.18] [%clk 0:04:22] } 8... Qb6?? { [%eval 1.99] [%clk 0:04:46] } 9. O-O?? { [%eval 2.32] [%clk 0:04:12] } 9... Bg4?? { [%eval 2.82] [%clk 0:04:44] } 10. Be2? { [%eval 1.3] [%clk 0:03:28] } 10... Bxf3? { [%eval 1.21] [%clk 0:04:42] } 11. Bxf3? { [%eval 1.4] [%clk 0:03:29] } 11... Qxd4? { [%eval 1.44] [%clk 0:04:42] } 12. Ne2? { [%eval -0.64] [%clk 0:03:24] } 12... Qd8? { [%eval 1.61] [%clk 0:04:41] } 13. Qc2? { [%eval -1.26] [%clk 0:03:16] } 13... Nbd7? { [%eval -1.48] [%clk 0:04:37] } 14. Rfd1? { [%eval -1.25] [%clk 0:03:16] } 14... e6? { [%eval -0.89] [%clk 0:04:36] } 15. Ng3?! { [%eval -1.85] [%clk 0:02:32] } 15... Qc7?! { [%eval -1.78] [%clk 0:04:36] } 16. a4?! { [%eval -2.1] [%clk 0:02:10] } 16... h5?! { [%eval -1.58] [%clk 0:04:30] } 17. Ne2?! { [%eval -1.92] [%clk 0:02:02] } 17... Ne5?! { [%eval -1.9] [%clk 0:04:30] } 18. Bf4?! { [%eval -2.19] [%clk 0:01:59] } 18... Nxf3+?! { [%eval -1.49] [%clk 0:04:28] } 19. gxf3?! { [%eval -1.46] [%clk 0:02:00] } 19... e5?! { [%eval -1.41] [%clk 0:03:56] } 20. Be3?! { [%eval -1.43] [%clk 0:01:57] } 20... Be7?! { [%eval -1.32] [%clk 0:03:29] } 21. Ng3?! { [%eval -1.72] [%clk 0:01:56] } 21... g6?! { [%eval -1.78] [%clk 0:03:21] } 22. a5?! { [%eval -1.82] [%clk 0:01:37] } 22... Qc8?! { [%eval -1.0] [%clk 0:03:18] } 23. Bc5?! { [%eval -1.69] [%clk 0:01:05] } 23... Bxc5?! { [%eval -1.45] [%clk 0:02:45] }";

    std::vector<Move> parsedMoves = parsePGN(pgn);

    for (const auto& move : parsedMoves) {
        std::cout << "White: " << move.whiteMove << " (Eval: " << move.whiteEval << ")" << std::endl;
        std::cout << "Black: " << move.blackMove << " (Eval: " << move.blackEval << ")" << std::endl;
    }

    return 0;
}
