//
// Created by totorroto on 21/12/23.
//

#ifndef TDDCHESS_CHESS_H
#define TDDCHESS_CHESS_H
using namespace std;

#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>

class ChessBoard;
class Chess;

class ChessPiece {
public:
    ChessPiece() = default;

    virtual ~ChessPiece() = default;

    virtual char getPiece() const = 0;

    virtual void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) = 0;

    virtual bool isWhitePiece() = 0;

    virtual bool isBlackPiece() = 0;

};

class NullPiece : public ChessPiece {
public:
    NullPiece() = default;

    ~NullPiece() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class WhitePawn : public ChessPiece {
public:
    WhitePawn() = default;

    ~WhitePawn() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class BlackPawn : public ChessPiece {
public:
    BlackPawn() = default;

    ~BlackPawn() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
private:

};
class Knight : public ChessPiece {
public:

    Knight(char color): color(color) {};

    ~Knight() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

private:
    char color;
};

class Bishop : public ChessPiece {
public:

    Bishop(char color): color(color) {};

    ~Bishop() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

private:
    char color;
};

class Rook : public ChessPiece {
public:

    Rook(char color): color(color) {};

    ~Rook() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

private:
    char color;
};

class Queen : public ChessPiece {
public:

    Queen(char color): color(color) {};

    ~Queen() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

private:
    char color;
};

class King : public ChessPiece {
public:

    King(char color): color(color) {};

    ~King() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

private:
    char color;
};


class ChessBoard {
public:
    ChessBoard();

    ~ChessBoard() = default;

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    shared_ptr<ChessPiece> getPieceAt(int row, int column);

    void printBoard();

    void setPiece(int row, int column, shared_ptr<ChessPiece> piece);

    bool isInCheck(char color);

    void setUpPieces();

private:
    shared_ptr<ChessPiece> board[8][8];

    pair<int,int> getKingPosition(char color);

};

class Chess {
public:
    Chess();

    ~Chess() = default;

    void startGame();

    void putPiece(int row, int column, char piece);

    char getPieceAt(int row, int column);

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhiteTurn() const;

    bool isBlackTurn() const;

    void printBoard();

    friend class ChessBoard;



private:
    ChessBoard board;
    char turn;

    void changeTurn();

    void
    undoMove(int initialRow, int initialColumn, int finishRow, int finishColumn, shared_ptr<ChessPiece> &eatenPiece);

    bool isInBadCheck();
};


#endif //TDDCHESS_CHESS_H
