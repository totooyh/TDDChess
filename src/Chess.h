//
// Created by totorroto on 21/12/23.
//


#ifndef TDDCHESS_CHESS_H
#define TDDCHESS_CHESS_H


#include <cctype>
#include <memory>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class ChessBoard;

class Chess;

class ChessPiece {
public:
    ChessPiece() = default;

    virtual ~ChessPiece() = default;

    virtual char getPiece() const = 0;

    virtual void
    assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) = 0;

    virtual bool isWhitePiece() = 0;

    virtual bool isBlackPiece() = 0;

    virtual char getColor() const = 0;

    virtual vector<string> possibleMoves(ChessBoard *board, int initialRow, int initialColumn) = 0;

private:
    char color;

};

class TangibleChessPiece : public ChessPiece {
public:
    TangibleChessPiece() = default;

    virtual ~TangibleChessPiece() = default;

    virtual char getPiece() const = 0;

    virtual void
    assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) = 0;

    virtual bool isWhitePiece() = 0;

    virtual bool isBlackPiece() = 0;

    virtual char getColor() const = 0;

    vector<string> possibleMoves(ChessBoard *board, int initialRow, int initialColumn);

private:
    char color;
};

class NullPiece : public ChessPiece {
public:
    NullPiece() = default;

    ~NullPiece() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

    vector<string> possibleMoves(ChessBoard *board, int initialRow, int initialColumn) override;

};

class WhitePawn : public TangibleChessPiece {
public:
    WhitePawn() {};

    ~WhitePawn() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

};

class BlackPawn : public TangibleChessPiece {
public:
    BlackPawn() {};

    ~BlackPawn() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

};

class Knight : public TangibleChessPiece {
public:

    Knight(char color) : color(color) {};

    ~Knight() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class Bishop : public TangibleChessPiece {
public:

    Bishop(char color) : color(color) {};

    ~Bishop() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class Rook : public TangibleChessPiece {
public:

    Rook(char color) : color(color) {};

    ~Rook() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class Queen : public TangibleChessPiece {
public:

    Queen(char color) : color(color) {};

    ~Queen() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class WhiteKing : public TangibleChessPiece {
public:

    WhiteKing() {};

    ~WhiteKing() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class BlackKing : public TangibleChessPiece {
public:

    BlackKing() {};

    ~BlackKing() = default;

    char getPiece() const override;

    void assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) override;

    bool isWhitePiece() override;

    bool isBlackPiece() override;

    char getColor() const override;

private:
    char color;
};

class ChessBoard {
public:
    ChessBoard();

    ~ChessBoard() = default;

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    static void assertIsInsideChessBoard(int initialRow, int initialColumn);

    static bool isOutsideChessBoard(int initialRow, int initialColumn);

    shared_ptr<ChessPiece> getPieceAt(int row, int column);

    void printBoard();

    void setPiece(int row, int column, shared_ptr<ChessPiece> piece);

    bool isInCheck(char color);

    void setUpPieces(char pieces[8][8]);

    void promotePawn(int row, int column);

    void choosePromotion(char choosenPiece);

    bool isPromotionTime();

private:
    shared_ptr<ChessPiece> board[8][8];

    pair<int, int> getKingPosition(char color);

    bool promoted;
    int promotionRow;
    int promotionColumn;
};

class Chess {
public:
    Chess();

    ~Chess() = default;

    void startGame(char initialPieces[8][8]);

    void putPiece(int row, int column, char piece);

    char getPieceAt(int row, int column);

    void movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn);

    void assertSelfKingIsNotAttacked(int initialRow, int initialColumn, int finishRow, int finishColumn,
                                     std::shared_ptr<ChessPiece> &pieceWhereThePieceFall);

    void assertCanMove(int initialRow, int initialColumn, int finishRow, int finishColumn);

    bool isWhiteTurn() const;

    bool isBlackTurn() const;

    void printBoard();

    friend class ChessBoard;

    void choosePromotion(char choosenPiece);

    vector<string> possibleMoves();

    bool isCheckMate();

private:
    ChessBoard board;
    char turn;
    char winner;
    bool gameOver;

    void changeTurn();

    void
    undoMove(int initialRow, int initialColumn, int finishRow, int finishColumn, shared_ptr<ChessPiece> &eatenPiece);

};

#endif //TDDCHESS_CHESS_H
