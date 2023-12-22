#include "../lib/googletest-main/googletest/include/gtest/gtest.h"

#include "../src/Chess.cpp"

int main(){
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}
class chessBoardTest : public testing:: Test{
protected:
  void SetUp() override {
    chessGame = Chess();
  }
  void simpleWhitePawnMove(){
    chessGame.movePiece(1, 6, 2, 6);
  }
  Chess chessGame;
};


TEST_F(chessBoardTest, whitePawnCanMoveOneSquareForward) {
  chessGame.movePiece(1, 0, 2, 0);
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), ' ');
}
TEST_F(chessBoardTest, cantMoveEmptySquare) {
  ASSERT_ANY_THROW(chessGame.movePiece(3, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(3, 0), ' ');
}
TEST_F(chessBoardTest, cantPassTheTurn) {
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 1, 0));
}
TEST_F(chessBoardTest, whitePawnCanNotMoveMoreThan2SquareFoward) {
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}

TEST_F(chessBoardTest, whitePawnCanNotMoveBackward) {
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 0, 0));
  ASSERT_EQ(chessGame.getPieceAt(0, 0), 'R');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}
TEST_F(chessBoardTest, afterWhiteTurnIsBlackTurn) {
  ASSERT_TRUE(chessGame.isWhiteTurn());
  simpleWhitePawnMove();
  ASSERT_TRUE(chessGame.isBlackTurn());
}
TEST_F(chessBoardTest, whiteCantMoveIfIsBlackTurn){
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 2, 0));
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), ' ');
}

TEST_F(chessBoardTest, whitePawnCanOnlyMoveTwiceIfIsFirstMove) {
  chessGame.movePiece(1, 0, 2, 0);
  ASSERT_ANY_THROW(chessGame.movePiece(2, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'P');
}
TEST_F(chessBoardTest, whitePawnCanNotMoveDiagonallyIfIsNotCapturing) {
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 2, 1));
  ASSERT_EQ(chessGame.getPieceAt(2, 1), ' ');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}

TEST_F(chessBoardTest, whitePawnCanMoveDiagonallyIfIsCapturing) {
  chessGame.movePiece(1, 0, 3, 0);
  chessGame.movePiece(6, 1, 4, 1);
  chessGame.movePiece(3, 0, 4, 1);
  ASSERT_EQ(chessGame.getPieceAt(3, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(4, 1), 'P');
}

TEST_F(chessBoardTest, whitePawnCanNotMoveFowardToACellWithAPiece) {
  chessGame.movePiece(1, 0, 3, 0);
  chessGame.movePiece(6, 0, 4, 0);
  ASSERT_ANY_THROW(chessGame.movePiece(3, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(3, 0), 'P');
}

TEST_F(chessBoardTest,blackCantMoveIfIsWhiteTurn){
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 5, 0));
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(5, 0), ' ');
}


TEST_F(chessBoardTest, blackPawnCanNotMoveBackward) {
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 7, 0));
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(7, 0), 'r');
}

TEST_F(chessBoardTest, blackPawnCanMoveOneSquareForward) {
  simpleWhitePawnMove();
  chessGame.movePiece(6, 0, 5, 0);
  ASSERT_EQ(chessGame.getPieceAt(5, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), ' ');
}

TEST_F(chessBoardTest, blackPawnCanMoveTwoSquaresForwardIfIsFirstMove) {
  simpleWhitePawnMove();
  chessGame.movePiece(6, 0, 4, 0);
  ASSERT_EQ(chessGame.getPieceAt(4, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), ' ');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveMoreThan2SquareFoward) {
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 3, 0));
  ASSERT_EQ(chessGame.getPieceAt(3, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveDiagonallyIfIsNotCapturing) {
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 5, 1));
  ASSERT_EQ(chessGame.getPieceAt(5, 1), ' ');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanMoveDiagonallyIfIsCapturing) {
  chessGame.movePiece(1, 0, 3, 0);
  chessGame.movePiece(6, 1, 4, 1);
  simpleWhitePawnMove();
  chessGame.movePiece(4, 1, 3, 0);
  ASSERT_EQ(chessGame.getPieceAt(4, 1), ' ');
  ASSERT_EQ(chessGame.getPieceAt(3, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveFowardToACellWithAPiece) {
  simpleWhitePawnMove();
  chessGame.movePiece(6, 0, 4, 0);
  chessGame.movePiece(1, 0, 3, 0);
  ASSERT_ANY_THROW(chessGame.movePiece(4, 0, 3, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(3, 0), 'P');
}

TEST_F(chessBoardTest, pawnCantJumpOverAPiece) {
  chessGame.movePiece(1,7,3,7);
  chessGame.movePiece(6, 0, 4, 0);
  chessGame.movePiece(3,7,4,7);
  chessGame.movePiece(4, 0, 3, 0);
  chessGame.movePiece(4,7,5,7);
  chessGame.movePiece(3, 0, 2, 0);
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 3, 0));
  chessGame.movePiece(1, 1, 3, 1);
  ASSERT_ANY_THROW(chessGame.movePiece(6, 7, 4, 7));
}

TEST_F(chessBoardTest, whitePiecesCantMoveToACellWithAPieceOfTheSameColor) {
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,1,0));
}

TEST_F(chessBoardTest, blackPiecesCantMoveToACellWithAPieceOfTheSameColor) {
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(7,0,6,0));
}

TEST_F(chessBoardTest,whiteKnightCanMoveInLShape){
  chessGame.movePiece(0,1,2,2);
  ASSERT_EQ(chessGame.getPieceAt(2,2),'N');
};

TEST_F(chessBoardTest,blackKnightCanMoveInLShape){
  simpleWhitePawnMove();
  chessGame.movePiece(7,1,5,2);
  ASSERT_EQ(chessGame.getPieceAt(5,2),'n');
};

TEST_F(chessBoardTest,whiteKnightCanNotMoveInNotLShape){
  ASSERT_ANY_THROW(chessGame.movePiece(0,1,2,3));
};

TEST_F(chessBoardTest,blackKnightCanNotMoveInNotLShape){
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(7,1,2,3));
};

TEST_F(chessBoardTest,bishopCanOnlyMoveDiagonally){
  ASSERT_ANY_THROW(chessGame.movePiece(0,2,0,4));
  ASSERT_EQ(chessGame.getPieceAt(0,2),'B');
};

TEST_F(chessBoardTest,bishopCantJumpPieces){
  ASSERT_ANY_THROW(chessGame.movePiece(0,2,2,4));
  ASSERT_EQ(chessGame.getPieceAt(0,2),'B');
}

TEST_F(chessBoardTest,rookCantMoveDiagonally){
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,1,1));
  ASSERT_EQ(chessGame.getPieceAt(0,0),'R');
};

TEST_F(chessBoardTest,rookCantJumpPieces){
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,0,2));
  ASSERT_EQ(chessGame.getPieceAt(0,0),'R');
}

TEST_F(chessBoardTest,queenCanMoveLikeARook){
  chessGame.movePiece(1,4,3,4);
  chessGame.movePiece(6,0,5,0);
  chessGame.movePiece(0,4,2,4);

  ASSERT_EQ(chessGame.getPieceAt(2,4),'Q');
};

TEST_F(chessBoardTest,queenCanMoveLikeABishop){
  chessGame.movePiece(1,3,3,3);
  chessGame.movePiece(6,0,5,0);
  chessGame.movePiece(0,4,4,0);

  ASSERT_EQ(chessGame.getPieceAt(4,0),'Q');
};
TEST_F(chessBoardTest,kingCantMove2SquaresAway){
  chessGame.movePiece(1,3,3,3);
  chessGame.movePiece(6,0,5,0);
  ASSERT_ANY_THROW(chessGame.movePiece(0,3,2,3));
  ASSERT_EQ(chessGame.getPieceAt(0,3),'K');
};

TEST_F(chessBoardTest,kingCanMoveOnlyOneSquareInAnyDirection){
  chessGame.movePiece(1,3,3,3);
  chessGame.movePiece(6,0,5,0);
  chessGame.movePiece(0,3,1,3);
  ASSERT_EQ(chessGame.getPieceAt(1,3),'K');
}

TEST_F(chessBoardTest,blackKingCantMoveAndFinishInCheck){
  chessGame.movePiece(1,3,3,3);
  chessGame.movePiece(6,2,5,2);
  chessGame.movePiece(0,4,4,0);
  ASSERT_ANY_THROW(chessGame.movePiece(5,2,4,3));
}

TEST_F(chessBoardTest,whiteCantMoveAndFinishInCheck){
  chessGame.movePiece(1,2,3,2);
  chessGame.movePiece(6,3,5,3);
  simpleWhitePawnMove();
  chessGame.movePiece(7,4,3,0);
  ASSERT_ANY_THROW(chessGame.movePiece(1,5,2,5));
}
