#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include <sstream>

class Board
{
public:
    Piece board[BOARD::ranks][BOARD::files] = {};
    int checks = 0;
    bool illegal = false;
    bool castle[BOARD::numOfCastlingRights] = {};
    INDEX enpassent;
    int fiftyMoves = 0;
    int materialBalance = 0;
    int turn = TURN::nothing;
    GameStatus status = GameStatus::STILL_GOING;
    std::string FEN = "";

    Board(std::string fen = BOARD::defaultFen)
    {
        // some code to convert fen string to the above members
        std::istringstream iss(fen);
        std::vector<std::string> modified_fen;

        do
        {
            std::string subs;
            iss >> subs;
            modified_fen.push_back(subs);
        } while (iss);

        int file = 0, rank = 7;
        int piece_id = 1;
        for (char s : modified_fen[0])
        {
            switch (s)
            {
            case 'p':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::PAWN;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::PAWN);
                file++;
                piece_id++;
                break;
            case 'n':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::KNIGHT;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::KNIGHT);
                file++;
                piece_id++;
                break;

            case 'b':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::BISHOP;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::BISHOP);
                file++;
                piece_id++;
                break;

            case 'r':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::ROOK;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::ROOK);
                file++;
                piece_id++;
                break;

            case 'q':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::QUEEN;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::QUEEN);
                file++;
                piece_id++;
                break;

            case 'k':
                boardIndex(INDEX{rank, file})->color = COLOR::black;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::KING;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance -= MATERIAL::pieceMaterial.at(PIECE::KING);
                file++;
                piece_id++;
                break;

            case 'P':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::PAWN;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::PAWN);
                file++;
                piece_id++;
                break;
            case 'N':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::KNIGHT;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::KNIGHT);
                file++;
                piece_id++;
                break;

            case 'B':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::BISHOP;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::BISHOP);
                file++;
                piece_id++;
                break;

            case 'R':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::ROOK;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::ROOK);
                file++;
                piece_id++;
                break;

            case 'Q':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::QUEEN;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::QUEEN);
                file++;
                piece_id++;
                break;

            case 'K':
                boardIndex(INDEX{rank, file})->color = COLOR::white;
                boardIndex(INDEX{rank, file})->pieceType = PIECE::KING;
                boardIndex(INDEX{rank, file})->index.setIndex(rank, file);
                boardIndex(INDEX{rank, file})->isEmpty = false;
                materialBalance += MATERIAL::pieceMaterial.at(PIECE::KING);
                file++;
                piece_id++;
                break;

            case '/':
                file = 0;
                rank--;
                break;
            default:
                int num = s - '0';
                for (int i = file; i < file + num; i++)
                {
                    boardIndex(INDEX{rank, i})->index.setIndex(rank, i);
                    materialBalance += MATERIAL::pieceMaterial.at(PIECE::EMPTY);
                }

                file += num;
                break;
            }
        }

        if (modified_fen[1] == "w")
            turn = 1;
        else
            turn = -1;

        for (char s : modified_fen[2])
        {
            switch (s)
            {
            case 'K':
                castle[BOARD::whiteKingSideCastleIndex] = true;
                break;
            case 'Q':
                castle[BOARD::whiteQueenSideCastleIndex] = true;
                break;
            case 'k':
                castle[BOARD::blackKingSideCastleIndex] = true;
                break;
            case 'q':
                castle[BOARD::blackQueenSideCastleIndex] = true;
                break;
            }
        }

        if (modified_fen[3] == "-")
            enpassent.strToIndex(SQUARE::emptyStr);
        else
        {
            enpassent.strToIndex(modified_fen[3]);
        }

        fiftyMoves = stoi(modified_fen[4]);
        FEN = fen;

        // moves
        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                boardIndex(INDEX{rank, file})->moves = pieceMoveGeneration(INDEX{rank, file});
            }
        }

        // Check();

        // generateMoves();
    }

    Piece *boardIndex(INDEX index)
    {
        return &board[index.rank][index.file];
    }

    void printBoard()
    {
        for (int rank = 7; rank >= 0; rank--)
        {
            for (int file = 0; file < 8; file++)
                std::cout << UI::pieceToChar.find(std::make_pair(boardIndex(INDEX{rank, file})->pieceType, boardIndex(INDEX{rank, file})->color))->second << " ";
            std::cout << '\n';
        }
        std::cout << std::endl;

        std::cout << "castle(KQkq) : " << castle[BOARD::whiteKingSideCastleIndex] << castle[BOARD::whiteQueenSideCastleIndex] << castle[BOARD::blackKingSideCastleIndex] << castle[BOARD::blackQueenSideCastleIndex] << std::endl;
        std::cout << "enpassent : " << enpassent.print() << std::endl;
        std::cout << "fifty moves : " << fiftyMoves << std::endl;
        std::cout << "material balance : " << materialBalance << std::endl;
        std::cout << "turn : " << turn << std::endl;
        std::cout << "FEN : " << FEN << std::endl;
        std::cout << "Checks : " << checks << std::endl;
        std::cout << "illegal : " << illegal << std::endl;
    }

    void update(INDEX from, INDEX to, bool halfMove = false);

    totalMoves moveGeneration();

    movesOfaPiece pieceMoveGeneration(INDEX index);

    movesInSingleDirection pieceMoveGenerationDirection(INDEX index, direction dir);

    void temp()
    {
        // for (auto i : board[index[0]][index[1]].watchingSquare)
        // {
        //     for (auto j : i.second)
        //     {
        //         std::cout << "dir : " << i.first[0] << "_" << i.first[1] << " | index : " << BOARD::indexToSquareName(j) << std::endl;
        //     }
        // }

        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                for (auto it : boardIndex(INDEX(rank, file))->watchingSquare)
                {
                    for (auto i : it.second)
                    {
                        std::cout << INDEX(rank, file).print() << " | index : " << i.print() << " | dir : " << it.first[0] << "_" << it.first[1] << std::endl;
                    }
                }
            }
        }
        std::cout << std::endl;

        for (int rank = 0; rank < 8; rank++)
        {
            for (int file = 0; file < 8; file++)
            {
                for (auto it : boardIndex(INDEX(rank, file))->watchers)
                {
                    std::cout << INDEX(rank, file).print() << " | index : " << it.first.print() << " | dir : " << it.second[0] << "_" << it.second[1] << std::endl;
                }
            }
        }
    }

    int attackers(INDEX index, int color)
    {
        int count = 0;
        for (auto i : boardIndex(index)->watchers)
        {
            if (boardIndex(i.first)->color == color)
                count++;
        }
        return count;
    }

    void playMove(Move moveData);

    bool operator==(const Board &other) const
    {
        return board == other.board;
    }

    Move notationsToIndex(std::string move);
};

#endif