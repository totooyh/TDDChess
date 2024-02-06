//
// Created by totorroto on 21/12/23.
//
//FEATURES
//Para hacer castle, hacer que el rey le diga a la torre, venite xd
//Para hacer el ampassant, acordarse siempre la ultima jugada, o solamente cuando es peon, ya fue, y te guardas donde esta, y despues en el peon chequeas en isCapture, si esta a la derecha/izquierda


//Refactorings TODO
// turn is an object
// mover promoted tambien?, como hacerlo, hacer 2 tipos de tangible pieces, normales(todas menos raras), raras(peon rey), asi me saco lo de color.

#include "Chess.h"

#include <utility>

using namespace std;

Chess::Chess() {
  board = ChessBoard();
  turn = 'w';
  winner = 'N';
  gameOver = false;
}

void Chess::startGame(char initialPieces[8][8]) {
  board.setUpPieces(initialPieces);
  if (isCheckMate()) {
    gameOver = true;
    winner = (turn == 'w') ? 'b' : 'w';
  }
}

bool Chess::isGameRunning() const {
  return !gameOver;
}

char Chess::getPieceAt(int row, int column) {
  return (board.getPieceAt(row, column))->getPiece();
}

void Chess::movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if (gameOver) {
    throw ("The game is over");
  }
  assertCanMove(initialRow, initialColumn, finishRow, finishColumn);
  //esto es medio una cagada, me gustaria de alguna manera agregarlo al assertCanMove, no debe ser imposible para nada, lo del rey digo.
  shared_ptr<ChessPiece> pieceWhereThePieceFall = board.getPieceAt(finishRow, finishColumn);
  board.movePiece(initialRow, initialColumn, finishRow, finishColumn);
  assertSelfKingIsNotAttacked(initialRow, initialColumn, finishRow, finishColumn, pieceWhereThePieceFall);
  changeTurn();
  if (isCheckMate()) {
    gameOver = true;
    winner = (turn == 'w') ? 'b' : 'w';
  }
}

void Chess::assertSelfKingIsNotAttacked(int initialRow, int initialColumn, int finishRow, int finishColumn,
                                        shared_ptr<ChessPiece> pieceWhereThePieceFall) {
  if (board.isInCheck(turn)) {
    undoMove(initialRow, initialColumn, finishRow, finishColumn, pieceWhereThePieceFall);
    throw invalid_argument("BRO! YOU ARE IN CHECK  WYD?");
  }
}

void Chess::assertCanMove(int initialRow, int initialColumn, int finishRow, int finishColumn) {
  assertIsInsideChessBoard(initialRow, initialColumn);
  assertIsInsideChessBoard(finishRow, finishColumn);
  shared_ptr<ChessPiece> piece = board.getPieceAt(initialRow, initialColumn);
  shared_ptr<ChessPiece> pieceWhereThePieceFall = board.getPieceAt(finishRow, finishColumn);

  if (piece->getColor() != turn) throw invalid_argument("Cant move opponent pieces");
  if (pieceWhereThePieceFall->getColor() == piece->getColor()) throw invalid_argument("Cant eat your own piece");

  if (board.isPromotionTime()) {
    throw invalid_argument("The other player must choose a promotion piece first");
  }

  if (initialRow == finishRow && initialColumn == finishColumn) {
    throw invalid_argument("Piece cant stay still");
  }

  shared_ptr<ChessPiece> pieceToMove = board.getPieceAt(initialRow, initialColumn);
  pieceToMove->assertCanMove(&board, initialRow, initialColumn, finishRow, finishColumn);
}

void Chess::undoMove(int initialRow, int initialColumn, int finishRow, int finishColumn,
                     shared_ptr<ChessPiece> eatenPiece) {
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
  turn = (turn == 'w') ? 'b' : 'w';
}

void Chess::printBoard() {
  board.printBoard();
}

void Chess::putPiece(int row, int column, char piece) {
  switch (piece) {
    case 'p':
      board.setPiece(row, column, make_shared<BlackPawn>());
      break;
    case 'P':
      board.setPiece(row, column, make_shared<WhitePawn>());
      break;
    case 'r':
      board.setPiece(row, column, make_shared<Rook>('b'));
      break;
    case 'R':
      board.setPiece(row, column, make_shared<Rook>('w'));
      break;
    case 'n':
      board.setPiece(row, column, make_shared<Knight>('b'));
      break;
    case 'N':
      board.setPiece(row, column, make_shared<Knight>('w'));
      break;
    case 'b':
      board.setPiece(row, column, make_shared<Bishop>('b'));
      break;
    case 'B':
      board.setPiece(row, column, make_shared<Bishop>('w'));
      break;
    case 'q':
      board.setPiece(row, column, make_shared<Queen>('b'));
      break;
    case 'Q':
      board.setPiece(row, column, make_shared<Queen>('w'));
      break;
    case 'k':
      board.setPiece(row, column, make_shared<BlackKing>());
      break;
    case 'K':
      board.setPiece(row, column, make_shared<WhiteKing>());
      break;
    default:
      board.setPiece(row, column, make_shared<NullPiece>());
      break;
  }
  if (isCheckMate()) {
    gameOver = true;
    winner = (turn == 'w') ? 'b' : 'w';
  }
}

void Chess::choosePromotion(char choosenPiece) {
  board.choosePromotion(choosenPiece);
}

vector<string> Chess::possibleMoves() {
  vector<string> possibleMoves = {};
  string move;
//TODO MEJORAR ESTO ES LENTO Y FEISIMO
  for (int fromRow = 0; fromRow < 8; fromRow++) {
    for (int fromColumn = 0; fromColumn < 8; fromColumn++) {
      for(int toRow = 0; toRow < 8; toRow++) {
        for(int toColumn = 0; toColumn < 8; toColumn++) {
          try {
            shared_ptr<ChessPiece>  eatenPiece = board.getPieceAt(toRow, toColumn);
            shared_ptr<ChessPiece> pieceToMove = board.getPieceAt(fromRow, fromColumn);
            assertCanMove(fromRow, fromColumn, toRow, toColumn);
            board.setPiece(toRow, toColumn, pieceToMove);
            board.setPiece(fromRow, fromColumn, make_shared<NullPiece>());
            assertSelfKingIsNotAttacked(fromRow, fromColumn, toRow, toColumn, eatenPiece);
            undoMove(fromRow, fromColumn, toRow, toColumn, eatenPiece);
            move = to_string(fromRow) + to_string(fromColumn) + to_string(toRow) + to_string(toColumn);
            possibleMoves.push_back(move);
          } catch (invalid_argument &e) {
            //do nothing
          }
        }
      }
    }
  }
  return possibleMoves;
}

bool Chess::isCheckMate() {
  return possibleMoves().empty() && board.isInCheck(turn);
}

bool Chess::isStaleMate(){
  return possibleMoves().empty() && !board.isInCheck(turn);
}

bool Chess::canShortCastle() {
  return board.canShortCastle(turn);
}

ChessBoard::ChessBoard() {
  for (auto &row : board)
    for (auto &cell: row) cell = make_shared<NullPiece>();

  promoted = false;
  promotionRow = -1;
  promotionColumn = -1;
}

void ChessBoard::setUpPieces(char pieces[8][8]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      switch (pieces[i][j]) {
        case 'p':
          board[i][j] = make_shared<BlackPawn>();
          break;
        case 'P':
          board[i][j] = make_shared<WhitePawn>();
          break;
        case 'r':
          board[i][j] = make_shared<Rook>('b');
          break;
        case 'R':
          board[i][j] = make_shared<Rook>('w');
          break;
        case 'n':
          board[i][j] = make_shared<Knight>('b');
          break;
        case 'N':
          board[i][j] = make_shared<Knight>('w');
          break;
        case 'b':
          board[i][j] = make_shared<Bishop>('b');
          break;
        case 'B':
          board[i][j] = make_shared<Bishop>('w');
          break;
        case 'q':
          board[i][j] = make_shared<Queen>('b');
          break;
        case 'Q':
          board[i][j] = make_shared<Queen>('w');
          break;
        case 'k':
          board[i][j] = make_shared<BlackKing>();
          break;
        case 'K':
          board[i][j] = make_shared<WhiteKing>();
          break;
        default:
          board[i][j] = make_shared<NullPiece>();
          break;
      }
    }
  }
}

void ChessBoard::movePiece(int initialRow, int initialColumn, int finishRow, int finishColumn) {
  shared_ptr<ChessPiece> piece = board[initialRow][initialColumn];
  if(piece->getPiece() == 'K'  && initialRow == finishRow && initialRow == 0){
    if(initialColumn == 4 && finishColumn == 6)
      movePiece(0, 7, 0, 5);
    if(initialColumn == 4 && finishColumn == 2)
      movePiece(0, 0, 0, 3);
  }
  if(piece->getPiece() == 'k'  && initialRow == finishRow && initialRow == 7){
    if(initialColumn == 4 && finishColumn == 6)
      movePiece(7, 7, 7, 5);
    if(initialColumn == 4 && finishColumn == 2)
      movePiece(7, 0, 7, 3);
  }

  if(piece->isPromoting(finishRow)){
    promotionRow = finishRow;
    promotionColumn = finishColumn;
    promoted = true;
  }
  board[finishRow][finishColumn] = piece;
  board[initialRow][initialColumn] = make_shared<NullPiece>();
}

void Chess::assertIsInsideChessBoard(int initialRow, int initialColumn) {
  if (isOutsideChessBoard(initialRow, initialColumn)) {

    throw invalid_argument("Piece cant be outside of chess board");
  }
}

bool Chess::isOutsideChessBoard(int initialRow, int initialColumn) {
  return initialRow < 0 || initialRow > 7 || initialColumn < 0 || initialColumn > 7;
}

shared_ptr<ChessPiece> ChessBoard::getPieceAt(int row, int column) {
  return board[row][column];
}

void ChessBoard::printBoard() {
  cout << "  A B C D E F G H" << endl;
  for (int i = 7; i >= 0; i--) {
    cout << i +1 << " ";
    for (int j = 0; j < 8; j++) {
      cout << board[i][j]->getPiece() << " ";
    }
    cout << endl;
  }
  cout << "  A B C D E F G H" << endl;
}

void ChessBoard::setPiece(int row, int column, shared_ptr<ChessPiece> piece) {
  board[row][column] = std::move(piece);
}

bool ChessBoard::isInCheck(char color) {
  pair<int, int> kingPosition = getKingPosition(color);
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      //TODO pensar esto, se puede sacar el if/ el if esta como el culo seguro
      if (board[i][j]->getColor() != color) {
        try {
          board[i][j]->assertCanMove(this, i, j, kingPosition.first, kingPosition.second);
          return true;
        } catch (invalid_argument &e) {
          //do nothing capaz se puece sacar este catch, si total no quiero hacer nada
        }
      }
    }
  }
  return false;

}

pair<int, int> ChessBoard::getKingPosition(char color) {
  //this can be optimized by keeping track of the King position
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      if (color == 'w' && board[i][j]->getPiece() == 'K') {
        return make_pair(i, j);
      }
      if (color == 'b' && board[i][j]->getPiece() == 'k') {
        return make_pair(i, j);
      }
    }
  }
  throw invalid_argument("Really? There is no king");
}

void ChessBoard::choosePromotion(char choosenPiece) {
  if (!promoted) {
    throw invalid_argument("Should not happen");
  }
  if (promotionRow != 0 && promotionRow != 7) {
    throw invalid_argument("Should not happen");
  }
  switch (choosenPiece) {
    case 'Q':
      board[promotionRow][promotionColumn] = make_shared<Queen>(board[promotionRow][promotionColumn]->getColor());
      break;
    case 'R':
      board[promotionRow][promotionColumn] = make_shared<Rook>(board[promotionRow][promotionColumn]->getColor());
      break;
    case 'B':
      board[promotionRow][promotionColumn] = make_shared<Bishop>(board[promotionRow][promotionColumn]->getColor());
      break;
    case 'N':
      board[promotionRow][promotionColumn] = make_shared<Knight>(board[promotionRow][promotionColumn]->getColor());
      break;
    default:
      throw invalid_argument("Invalid promotion piece");
  }
  promoted = false;
}

bool ChessBoard::isPromotionTime() const {
  return promoted;
}

bool ChessBoard::canShortCastle(char color) {
  if (color == 'b') {
    if(board[7][5]->getPiece() != ' ' || board[7][6]->getPiece() != ' ' || board[7][7]->getPiece() != 'r'){
      return false;
    }
  }else{
    if(board[0][5]->getPiece() != ' ' || board[0][6]->getPiece() != ' ' || board[0][7]->getPiece() != 'R'){
      return false;
    }
  }
  return !isInCheck(color); //me falta ver que no este en jaque, voy a hacer una funcion que me diga si hay piezas atacando a una casilla
//      && !isInCheckAfterMove(color, 4, 0, 4, 1)
//      && !isInCheckAfterMove(color, 4, 0, 4, 2);
}

bool ChessBoard::canLongCastle(char color) {
  if (color == 'b') {
    if(board[7][3]->getPiece() != ' ' || board[7][2]->getPiece() != ' ' || board[7][1]->getPiece() != ' ' || board[7][0]->getPiece() != 'r'){
      return false;
    }
  }else{
    if(board[0][3]->getPiece() != ' ' || board[0][2]->getPiece() != ' ' || board[0][1]->getPiece() != ' ' || board[0][0]->getPiece() != 'R'){
      return false;
    }
  }
  return !isInCheck(color); //me falta ver que no este en jaque, voy a hacer una funcion que me diga si hay piezas atacando a una casilla
//      && !isInCheckAfterMove(color, 4, 0, 4, 1)
//      && !isInCheckAfterMove(color, 4, 0, 4, 2);
}



vector<string> TangibleChessPiece::possibleMoves(ChessBoard *board, int initialRow, int initialColumn) {
  vector<string> possibleMoves = {};
  string move;
  //chequear que no vaya al reves finishRow y finishColumn
  for (int finishRow = 0; finishRow < 8; finishRow++) {
    for (int finishColumn = 0; finishColumn < 8; finishColumn++) {
      try {
        assertCanMove(board, initialRow, initialColumn, finishRow, finishColumn);
        move = to_string(initialRow * 1000 + initialColumn * 100 + finishRow * 10 + finishColumn);
        possibleMoves.push_back(move);
      }catch (const std::exception &e) {
        //do nothing
      }
    }
  }
  return possibleMoves;
}

char NullPiece::getPiece() const {
  return ' ';
}

void NullPiece::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  throw invalid_argument("There is no piece");
}

bool NullPiece::isWhitePiece() {
  return false;
}

bool NullPiece::isBlackPiece() {
  return false;
}

char NullPiece::getColor() const {
  return ' ';
}

vector<string> NullPiece::possibleMoves(ChessBoard *board, int initialRow, int initialColumn) {
  return {};
}

bool NullPiece::isPromoting(int row) {
  return false;
}

char WhitePawn::getPiece() const {
  return 'P';
}

void WhitePawn::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  bool isCapture = false;
  if (finishRow - initialRow > 2) {
    throw invalid_argument("Pawn cant move that far");
  }
  if (finishRow < initialRow) {
    throw invalid_argument("Pawn cant move backwards");
  }
  if (initialRow != 1 && finishRow - initialRow >= 2) {
    throw invalid_argument("Pawn can only move 2 spaces in the first move");
  }
  if (initialRow == 1 && finishRow - initialRow == 2) {
    if (board->getPieceAt(initialRow + 1, initialColumn)->getPiece() != ' ') {
      throw invalid_argument("Pawn cant jump pieces");
    }
  }
  if (abs(initialColumn - finishColumn) == 1) {
    isCapture = true;
    if (board->getPieceAt(finishRow, finishColumn)->getPiece() == ' ') {
      throw invalid_argument("Pawn cant change lines if not capturing");
    }
  }
  if (abs(initialColumn - finishColumn) > 1) {
    throw invalid_argument("Pawn cant change lines if not capturing");
  }
  if (board->getPieceAt(finishRow, finishColumn)->getPiece() != ' ' && not isCapture) {
    throw invalid_argument("Pawn cant capture that way");
  }
}

bool WhitePawn::isWhitePiece() {
  return true;
}

bool WhitePawn::isBlackPiece() {
  return false;
}

char WhitePawn::getColor() const {
  return 'w';
}

bool WhitePawn::isPromoting(int row) {
  return (row == 7);
}

char BlackPawn::getPiece() const {
  return 'p';
}

void BlackPawn::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  bool isCapture = false;
  if (initialRow - finishRow > 2) {
    throw invalid_argument("Pawn cant move that far");
  }

  if (finishRow > initialRow) {
    throw invalid_argument("Pawn cant move backwards");
  }

  if (initialRow != 6 && initialRow - finishRow >= 2) {
    throw invalid_argument("Pawn can only move 2 spaces in the first move");
  }

  if (initialRow == 6 && initialRow - finishRow == 2) {
    if (board->getPieceAt(initialRow - 1, initialColumn)->getPiece() != ' ') {
      throw invalid_argument("Pawn cant jump pieces");
    }
  }

  if (abs(initialColumn - finishColumn) == 1) {
    isCapture = true;
    if (board->getPieceAt(finishRow, finishColumn)->getPiece() == ' ') {
      throw invalid_argument("Pawn cant change lines if not capturing");

    }
  }
  if (abs(initialColumn - finishColumn) > 1) {
    throw invalid_argument("Pawn cant change lines if not capturing");
  }
  if (board->getPieceAt(finishRow, finishColumn)->getPiece() != ' ' && not isCapture) {
    throw invalid_argument("Pawn cant capture that way");
  }

}

bool BlackPawn::isWhitePiece() {
  return false;
}

bool BlackPawn::isBlackPiece() {
  return true;
}

char BlackPawn::getColor() const {
  return 'b';
}

bool BlackPawn::isPromoting(int row) {
  return row == 0;
}

char Knight::getPiece() const {
  return color == 'w' ? 'N' : 'n';
}

void Knight::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if (abs(initialRow - finishRow) == 2 && abs(initialColumn - finishColumn) == 1) {
    return;
  }
  if (abs(initialRow - finishRow) == 1 && abs(initialColumn - finishColumn) == 2) {
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

char Knight::getColor() const {
  return color;
}

bool Knight::isPromoting(int row) {
  return false;
}

char Bishop::getPiece() const {
  return color == 'w' ? 'B' : 'b';
}

void Bishop::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if (abs(initialRow - finishRow) != abs(initialColumn - finishColumn)) {
    throw invalid_argument("Bishop cant move that way");
  }
  int rowDirection = (finishRow - initialRow) / abs(finishRow - initialRow);
  int columnDirection = (finishColumn - initialColumn) / abs(finishColumn - initialColumn);
  for (int i = 1; i < abs(initialRow - finishRow); i++) {
    if (board->getPieceAt(initialRow + i * rowDirection, initialColumn + i * columnDirection)->getPiece() != ' ') {
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

char Bishop::getColor() const {
  return color;
}

bool Bishop::isPromoting(int row) {
  return false;
}

char Rook::getPiece() const {
  return color == 'w' ? 'R' : 'r';
}

void Rook::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if (initialRow != finishRow && initialColumn != finishColumn) {
    throw invalid_argument("Rook cant move diagonally");
  }
  int direction;
  //mucho codigo repetido, mejorable
  if (initialRow == finishRow) {
    direction = (finishColumn - initialColumn) / abs(finishColumn - initialColumn);//1 or -1
    for (int i = 1; i < abs(initialColumn - finishColumn); i++) {
      if (board->getPieceAt(initialRow, initialColumn + i * direction)->getPiece() != ' ') {
        throw invalid_argument("Rook cant jump pieces");
      }
    }
  } else {
    direction = (finishRow - initialRow) / abs(finishRow - initialRow);//1 or -1
    for (int i = 1; i < abs(initialRow - finishRow); i++) {
      if (board->getPieceAt(initialRow, initialColumn + i * direction)->getPiece() != ' ') {
        throw invalid_argument("Rook cant jump pieces");
      }
    }
  }

}

bool Rook::isWhitePiece() {
  return color == 'w';
}

bool Rook::isBlackPiece() {
  return color == 'b';
}

char Rook::getColor() const {
  return color;
}

bool Rook::isPromoting(int row) {
  return false;
}

char Queen::getPiece() const {
  return color == 'w' ? 'Q' : 'q';
}

void Queen::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  //Se pueden mejorar los throws de las exceptions, tiran nombres con rook y bishop
  if (initialRow == finishRow || initialColumn == finishColumn) {
    Rook('b').assertCanMove(board, initialRow, initialColumn, finishRow, finishColumn);
  } else {
    Bishop('b').assertCanMove(board, initialRow, initialColumn, finishRow, finishColumn);
  }

}

bool Queen::isWhitePiece() {
  return color == 'w';
}

bool Queen::isBlackPiece() {
  return color == 'b';
}

char Queen::getColor() const {
  return color;
}

bool Queen::isPromoting(int row) {
  return false;
}

char WhiteKing::getPiece() const {
  return 'K';
}

void WhiteKing::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {
  if(initialRow == finishRow && initialRow == 0  && finishColumn - initialColumn == 2 && board->canShortCastle('w')){
    return;
  }

  if(initialRow == finishRow && initialRow ==0 && initialColumn - finishColumn == 2 && board->canLongCastle('w')){
    return;
  }
  if (abs(initialRow - finishRow) > 1 || abs(initialColumn - finishColumn) > 1) {
    throw invalid_argument("WhiteKing cant move that far");
  }

}

bool WhiteKing::isWhitePiece() {
  return true;
}

bool WhiteKing::isBlackPiece() {
  return false;
}

char WhiteKing::getColor() const {
  return 'w';
}

bool WhiteKing::isPromoting(int row) {
  return false;
}

char BlackKing::getPiece() const {
  return 'k';
}

void BlackKing::assertCanMove(ChessBoard *board, int initialRow, int initialColumn, int finishRow, int finishColumn) {

  if(initialRow == finishRow && initialRow == 7  && finishColumn - initialColumn == 2 && board->canShortCastle('b')){
    return;
  }

  if(initialRow == finishRow  && initialRow == 7 && initialColumn - finishColumn == 2 && board->canLongCastle('b')){
    return;
  }

  if (abs(initialRow - finishRow) > 1 || abs(initialColumn - finishColumn) > 1) {
    throw invalid_argument("King cant move that far");
  }

}

bool BlackKing::isWhitePiece() {
  return false;
}

bool BlackKing::isBlackPiece() {
  return true;
}

char BlackKing::getColor() const {
  return 'b';
}

bool BlackKing::isPromoting(int row) {
  return false;
}
