//
// Created by totorroto on 21/12/23.
//

#include "Chess.h"
using namespace  std;



Chess::Chess() {
  board = ChessBoard();
  turn = 'w';
}

char Chess::getPieceAt(int row, int column) {
    return (board.getPieceAt(row, column))->getPiece();
}

void Chess::movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(isWhiteTurn()){
    if(board.getPieceAt(initialRow, initialColumn)->isBlackPiece()){
      throw invalid_argument("Cant move opponent pieces");
    }
    if(board.getPieceAt(finishRow, finishColumn)->isWhitePiece()){
      throw invalid_argument("Cant move to a cell with a piece of the same color");
    }
  }else{
    if(board.getPieceAt(initialRow, initialColumn)->isWhitePiece()){
      throw invalid_argument("Cant move opponent pieces");
    }
    if(board.getPieceAt(finishRow, finishColumn)->isBlackPiece()){
      throw invalid_argument("Cant move to a cell with a piece of the same color");
    }
  }

  board.movePiece(initialRow, initialColumn, finishRow, finishColumn);
  changeTurn();
}

bool Chess::isWhiteTurn() const {
  return turn == 'w';
}

bool Chess::isBlackTurn() const {
  return turn == 'b';
}

void Chess::changeTurn() {
  if(turn == 'w'){
    turn = 'b';
  }else{
    turn = 'w';
  }

}



ChessBoard::ChessBoard() {
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      board[i][j] = make_shared<NullPiece>();
    }
  }

  for(int i = 0; i < 8; i++){
    board[1][i] = make_shared<WhitePawn>();
    board[6][i] = make_shared<BlackPawn>();
  }
  board[0][0] = make_shared<WhiteRook>();
  board[0][1] = make_shared<WhiteKnight>();
  board[0][2] = make_shared<WhiteBishop>();
  board[0][3] = make_shared<WhiteQueen>();
  board[0][4] = make_shared<WhiteKing>();
  board[0][5] = make_shared<WhiteBishop>();
  board[0][6] = make_shared<WhiteKnight>();
  board[0][7] = make_shared<WhiteRook>();

  board[7][0] = make_shared<BlackRook>();
  board[7][1] = make_shared<BlackKnight>();
  board[7][2] = make_shared<BlackBishop>();
  board[7][3] = make_shared<BlackQueen>();
  board[7][4] = make_shared<BlackKing>();
  board[7][5] = make_shared<BlackBishop>();
  board[7][6] = make_shared<BlackKnight>();
  board[7][7] = make_shared<BlackRook>();


}

void ChessBoard::movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(initialRow == finishRow && initialColumn == finishColumn){
    throw invalid_argument("The initial position and the final position are the same");
  }
  if(initialRow < 0 || initialRow > 7 || initialColumn < 0 || initialColumn > 7){
    throw invalid_argument("The initial position is out of the board");
  }
  board[initialRow][initialColumn]->assertCanMove(this, initialRow, initialColumn, finishRow, finishColumn);
  board[finishRow][finishColumn] = board[initialRow][initialColumn];
  board[initialRow][initialColumn] = make_shared<NullPiece>();
}

shared_ptr<ChessPiece> ChessBoard::getPieceAt(int row, int column) {
  return board[row][column];
}

char NullPiece::getPiece() const {
  return ' ';
}

void NullPiece::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  throw invalid_argument("There is no piece in the initial position");
}

bool NullPiece::isWhitePiece(){
  return false;
}

bool NullPiece::isBlackPiece(){
  return false;
}


char WhitePawn::getPiece() const {
  return 'P';
}

void WhitePawn::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  bool isCapture = false;
  if(finishRow - initialRow >2){
    throw invalid_argument("Pawn cant move that far");
  }
  if(finishRow < initialRow){
    throw invalid_argument("Pawn cant move backwards");
  }
  if(initialRow != 1 && finishRow - initialRow >= 2){
    throw invalid_argument("Pawn can only move 2 spaces in the first move");
  }
  if(initialRow == 1 && finishRow - initialRow == 2){
    if(board->getPieceAt(initialRow+1,initialColumn)->getPiece() != ' '){
      throw invalid_argument("Pawn cant jump pieces");
    }
  }
  if(abs(initialColumn-finishColumn)==1){
    isCapture = true;
    if(board->getPieceAt(finishRow,finishColumn)->getPiece() == ' '){
      throw invalid_argument("Pawn cant change lines if not capturing");
    }
  }
  if(abs(initialColumn-finishColumn)>1){
    throw invalid_argument("Pawn cant change lines if not capturing");
  }
  if(board->getPieceAt(finishRow,finishColumn)->getPiece() != ' ' && not isCapture){
    throw invalid_argument("Pawn cant capture that way");
  }
}

bool WhitePawn::isWhitePiece() {
  return true;
}

bool WhitePawn::isBlackPiece() {
  return false;
}

char BlackPawn::getPiece() const {
  return 'p';
}

void BlackPawn::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  bool isCapture = false;
  if(initialRow - finishRow > 2){
    throw invalid_argument("Pawn cant move that far");

  }

  if(finishRow > initialRow){
    throw invalid_argument("Pawn cant move backwards");

  }

  if(initialRow != 6 && initialRow - finishRow >= 2){
    throw invalid_argument("Pawn can only move 2 spaces in the first move");

  }

  if(initialRow == 6 && initialRow - finishRow == 2){
    if(board->getPieceAt(initialRow-1, initialColumn)->getPiece() != ' '){
      throw invalid_argument("Pawn cant jump pieces");
    }
  }

  if(abs(initialColumn - finishColumn) == 1){
    isCapture = true;
    if(board->getPieceAt(finishRow, finishColumn)->getPiece() == ' '){
      throw invalid_argument("Pawn cant change lines if not capturing");

    }
  }
  if(abs(initialColumn - finishColumn) > 1){
    throw invalid_argument("Pawn cant change lines if not capturing");
  }
  if(board->getPieceAt(finishRow, finishColumn)->getPiece() != ' ' && not isCapture){
    throw invalid_argument("Pawn cant capture that way");
  }
}

bool BlackPawn::isWhitePiece() {
  return false;
}

bool BlackPawn::isBlackPiece() {
  return true;
}


char WhiteKnight::getPiece() const {
  return 'N';
}

void WhiteKnight::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(abs(initialRow-finishRow) == 2 && abs(initialColumn-finishColumn) == 1){
    return;
  }
  if(abs(initialRow-finishRow) == 1 && abs(initialColumn-finishColumn) == 2){
    return;
  }
  throw invalid_argument("Knight cant move that way");
}

bool WhiteKnight::isWhitePiece() {
  return true;
}

bool WhiteKnight::isBlackPiece() {
  return false;
}

char BlackKnight::getPiece() const {
  return 'n';
}

void BlackKnight::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(abs(initialRow-finishRow) == 2 && abs(initialColumn-finishColumn) == 1){
    return;
  }
  if(abs(initialRow-finishRow) == 1 && abs(initialColumn-finishColumn) == 2){
    return;
  }
  throw invalid_argument("Knight cant move that way");
}

bool BlackKnight::isWhitePiece() {
  return false;
}

bool BlackKnight::isBlackPiece() {
  return true;
}

char WhiteBishop::getPiece() const {
  return 'B';
}

void WhiteBishop::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool WhiteBishop::isWhitePiece() {
  return true;
}

bool WhiteBishop::isBlackPiece() {
  return false;
}

char BlackBishop::getPiece() const {
  return 'b';
}

void BlackBishop::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool BlackBishop::isWhitePiece() {
  return false;
}

bool BlackBishop::isBlackPiece() {
  return true;
}


char WhiteRook::getPiece() const {
  return 'R';
}

void WhiteRook::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool WhiteRook::isWhitePiece() {
  return true;
}

bool WhiteRook::isBlackPiece() {
  return false;
}

char BlackRook::getPiece() const {
  return 'r';
}

void BlackRook::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool BlackRook::isWhitePiece() {
  return false;
}

bool BlackRook::isBlackPiece() {
  return true;
}

char WhiteQueen::getPiece() const {
  return 'Q';
}

void WhiteQueen::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool WhiteQueen::isWhitePiece() {
  return true;
}

bool WhiteQueen::isBlackPiece() {
  return false;
}

char BlackQueen::getPiece() const {
  return 'q';
}

void BlackQueen::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool BlackQueen::isWhitePiece() {
  return false;
}

bool BlackQueen::isBlackPiece() {
  return true;
}

char WhiteKing::getPiece() const {
  return 'K';
}

void WhiteKing::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool WhiteKing::isWhitePiece() {
  return true;
}

bool WhiteKing::isBlackPiece() {
  return false;
}

char BlackKing::getPiece() const {
  return 'k';
}

void BlackKing::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

}

bool BlackKing::isWhitePiece() {
  return false;
}

bool BlackKing::isBlackPiece() {
  return true;
}
