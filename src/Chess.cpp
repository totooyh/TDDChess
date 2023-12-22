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
  shared_ptr<ChessPiece> piece = board.getPieceAt(initialRow, initialColumn);
  shared_ptr<ChessPiece> toFallPieceRN = board.getPieceAt(finishRow, finishColumn);
  if(isWhiteTurn()){
    if(piece->isBlackPiece()){
      throw invalid_argument("Cant move opponent pieces");
    }
    if(toFallPieceRN->isWhitePiece()){
      throw invalid_argument("Cant move to a cell with a piece of the same color");
    }
  }else{
    if(piece->isWhitePiece()){
      throw invalid_argument("Cant move opponent pieces");
    }
    if(toFallPieceRN->isBlackPiece()){
      throw invalid_argument("Cant move to a cell with a piece of the same color");
    }
  }

  board.movePiece(initialRow, initialColumn, finishRow, finishColumn);
  if(this->isInBadCheck()){
    undoMove(initialRow, initialColumn, finishRow, finishColumn, toFallPieceRN);
    throw invalid_argument("BRO! YOU ARE IN CHECK  WYD?");
  }
  changeTurn();
}

void
Chess::undoMove(int initialRow, int initialColumn, int finishRow, int finishColumn,
                shared_ptr<ChessPiece> &eatenPiece) {
  board.setPiece(initialRow, initialColumn, board.getPieceAt(finishRow, finishColumn));
  board.setPiece(finishRow, finishColumn, eatenPiece);
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

void Chess::printBoard() {
  board.printBoard();
}

bool Chess::isInBadCheck() {
  if(turn == 'w'){
    return board.isInCheck('w');
}else{
    return board.isInCheck('b');
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
  board[0][0] = make_shared<Rook>('w');
  board[0][1] = make_shared<Knight>('w');
  board[0][2] = make_shared<Bishop>('w');
  board[0][3] = make_shared<King>('w');
  board[0][4] = make_shared<Queen>('w');
  board[0][5] = make_shared<Bishop>('w');
  board[0][6] = make_shared<Knight>('w');
  board[0][7] = make_shared<Rook>('w');

  board[7][0] = make_shared<Rook>('b');
  board[7][1] = make_shared<Knight>('b');
  board[7][2] = make_shared<Bishop>('b');
  board[7][3] = make_shared<King>('b');
  board[7][4] = make_shared<Queen>('b');
  board[7][5] = make_shared<Bishop>('b');
  board[7][6] = make_shared<Knight>('b');
  board[7][7] = make_shared<Rook>('b');




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

void ChessBoard::printBoard() {
  //print reverse board



  cout << "  0 1 2 3 4 5 6 7" << endl;
  for(int i = 7; i >= 0; i--){
    cout << i << " ";
    for(int j = 0; j < 8; j++){
      cout << board[i][j]->getPiece() << " ";
    }
    cout << endl;
  }
}

void ChessBoard::setPiece(int row, int column, shared_ptr<ChessPiece> piece) {
  board[row][column] = piece;
}

bool ChessBoard::isInCheck(char color) {
  pair<int,int> kingPosition = getKingPosition(color);
  if(color == 'w'){
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        if(board[i][j]->isBlackPiece()){
          try{
            board[i][j]->assertCanMove(this, i, j, kingPosition.first, kingPosition.second);
            return true;
          }catch (invalid_argument &e){
            //do nothing
          }
        }
      }
    }
    return false;
  }else{
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 8; j++){
        if(board[i][j]->isWhitePiece()){
          try{
            board[i][j]->assertCanMove(this, i, j, kingPosition.first, kingPosition.second);
            return true;
          }catch (invalid_argument &e){
            //do nothing
          }
        }
      }
    }
    return false;
  }
}

pair<int,int> ChessBoard::getKingPosition(char color) {
  //this can be optimized by keeping track of the king position
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(color == 'w' && board[i][j]->getPiece() == 'K'){
        return make_pair(i,j);
      }
      if(color == 'b' && board[i][j]->getPiece() == 'k'){
        return make_pair(i,j);
      }
    }
  }
  throw invalid_argument("Really? There is no white king");
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


char Knight::getPiece() const {
  return color == 'w' ? 'N' : 'n';
}

void Knight::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(abs(initialRow - finishRow) == 2 && abs(initialColumn - finishColumn) == 1){
    return;
  }
  if(abs(initialRow - finishRow) == 1 && abs(initialColumn - finishColumn) == 2){
    return;
  }
  throw invalid_argument("Knight cant move that way");
}

bool Knight::isWhitePiece() {
  return color == 'w';
}

bool Knight::isBlackPiece() {
  return color == 'b';
}

char Bishop::getPiece() const {
  return color == 'w' ? 'B' : 'b';
}

void Bishop::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(abs(initialRow - finishRow) != abs(initialColumn - finishColumn)){
    throw invalid_argument("Bishop cant move that way");
  }
  int rowDirection = (finishRow - initialRow) / abs(finishRow - initialRow);
  int columnDirection = (finishColumn - initialColumn) / abs(finishColumn - initialColumn);
  for(int i = 1; i < abs(initialRow - finishRow); i++){
    if(board->getPieceAt(initialRow + i * rowDirection, initialColumn + i * columnDirection)->getPiece() != ' '){
      throw invalid_argument("Bishop cant jump pieces");
    }
  }
}

bool Bishop::isWhitePiece() {
  return color == 'w';
}

bool Bishop::isBlackPiece() {
  return color == 'b';
}

char Rook::getPiece() const {
  return color == 'w' ? 'R' : 'r';
}

void Rook::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(initialRow != finishRow && initialColumn != finishColumn){
    throw invalid_argument("Rook cant move diagonally");
  }
  int direction;
  if(initialRow == finishRow){
    direction = (finishColumn - initialColumn) / abs(finishColumn - initialColumn);
  }else{
    direction = (finishRow - initialRow) / abs(finishRow - initialRow);
  }
  for(int i = 1; i < abs(initialColumn - finishColumn); i++){
    if(board->getPieceAt(initialRow, initialColumn + i * direction)->getPiece() != ' '){
      throw invalid_argument("Rook cant jump pieces");
    }
  }
}

bool Rook::isWhitePiece() {
  return color == 'w';
}

bool Rook::isBlackPiece() {
  return color == 'b';
}

char Queen::getPiece() const {
  return color == 'w' ? 'Q' : 'q';
}

void Queen::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(initialRow == finishRow || initialColumn == finishColumn){
    Rook('b').assertCanMove(board, initialRow, initialColumn, finishRow, finishColumn);
  }else{
    Bishop('b').assertCanMove(board, initialRow, initialColumn, finishRow, finishColumn);
  }
}

bool Queen::isWhitePiece() {
  return color == 'w';
}

bool Queen::isBlackPiece() {
  return color == 'b';
}

char King::getPiece() const {
  return color == 'w' ? 'K' : 'k';
}

void King::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(abs(initialRow - finishRow) > 1 || abs(initialColumn - finishColumn) > 1){
    throw invalid_argument("King cant move that far");
  }
}

bool King::isWhitePiece() {
  return color == 'w';
}

bool King::isBlackPiece() {
  return color == 'b';
}
