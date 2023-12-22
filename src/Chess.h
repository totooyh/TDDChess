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
};
class WhiteKnight : public ChessPiece {
public:
    WhiteKnight() = default;

    ~WhiteKnight() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class BlackKnight : public ChessPiece {
public:
    BlackKnight() = default;

    ~BlackKnight() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class WhiteBishop : public ChessPiece {
public:
    WhiteBishop() = default;

    ~WhiteBishop() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class BlackBishop : public ChessPiece {
public:
    BlackBishop() = default;

    ~BlackBishop() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class WhiteRook : public ChessPiece {
public:
    WhiteRook() = default;

    ~WhiteRook() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

};

class BlackRook : public ChessPiece {
public:
    BlackRook() = default;

    ~BlackRook() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class WhiteQueen : public ChessPiece {
public:
    WhiteQueen() = default;

    ~WhiteQueen() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class BlackQueen : public ChessPiece {
public:
    BlackQueen() = default;

    ~BlackQueen() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class WhiteKing : public ChessPiece {
public:
    WhiteKing() = default;

    ~WhiteKing() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};

class BlackKing : public ChessPiece {
public:
    BlackKing() = default;

    ~BlackKing() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhitePiece() override;

    bool isBlackPiece() override;
};



class ChessBoard {
public:
    ChessBoard();

    ~ChessBoard() = default;

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    shared_ptr<ChessPiece> getPieceAt(int row, int column);
private:
    shared_ptr<ChessPiece> board[8][8];
};

class Chess {
public:
    Chess();

    ~Chess() = default;

    char getPieceAt(int row, int column);

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhiteTurn() const;

    bool isBlackTurn() const;

    friend class ChessBoard;
private:
    ChessBoard board;
    char turn;

    void changeTurn();
};


#endif //TDDCHESS_CHESS_H
