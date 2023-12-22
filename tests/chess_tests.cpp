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
    chessGame.putPiece(0, 3, 'K');
    chessGame.putPiece(7, 3, 'k');

  }
  void simpleWhitePawnMove(){
    chessGame.putPiece(1,6, 'P');
    chessGame.movePiece(1, 6, 2, 6);
  }
  Chess chessGame;
};


TEST_F(chessBoardTest, whitePawnCanMoveOneSquareForward) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.movePiece(1, 0, 2, 0);
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), ' ');
}
TEST_F(chessBoardTest, cantMoveEmptySquare) {
  ASSERT_ANY_THROW(chessGame.movePiece(3, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(3, 0), ' ');
}
TEST_F(chessBoardTest, cantPassTheTurn) {
  chessGame.putPiece(1, 0, 'P');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 1, 0));
}
TEST_F(chessBoardTest, whitePawnCanNotMoveMoreThan2SquareFoward) {
  chessGame.putPiece(1, 0, 'P');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}

TEST_F(chessBoardTest, whitePawnCanNotMoveBackward) {
  chessGame.putPiece(1, 0, 'P');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 0, 0));
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}
TEST_F(chessBoardTest, afterWhiteTurnIsBlackTurn) {
  ASSERT_TRUE(chessGame.isWhiteTurn());
  simpleWhitePawnMove();
  ASSERT_TRUE(chessGame.isBlackTurn());
}
TEST_F(chessBoardTest, whiteCantMoveIfIsBlackTurn){
  simpleWhitePawnMove();
  chessGame.putPiece(1, 0, 'P');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 2, 0));
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), ' ');
}

TEST_F(chessBoardTest, whitePawnCanOnlyMoveTwiceIfIsFirstMove) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.movePiece(1, 0, 2, 0);
  chessGame.putPiece(6, 0, 'p');
  chessGame.movePiece(6,0,5,0);
  ASSERT_ANY_THROW(chessGame.movePiece(2, 0, 4, 0));
  ASSERT_EQ(chessGame.getPieceAt(4, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'P');
}
TEST_F(chessBoardTest, whitePawnCanNotMoveDiagonallyIfIsNotCapturing) {
  chessGame.putPiece(1, 0, 'P');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 2, 1));
  ASSERT_EQ(chessGame.getPieceAt(2, 1), ' ');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
}

TEST_F(chessBoardTest, whitePawnCanMoveDiagonallyIfIsCapturing) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.putPiece(2, 1, 'p');
  chessGame.movePiece(1, 0, 2, 1);
  ASSERT_EQ(chessGame.getPieceAt(2, 1), 'P');
  ASSERT_EQ(chessGame.getPieceAt(1, 0), ' ');
}

TEST_F(chessBoardTest, whitePawnCanNotMoveFowardToACellWithAPiece) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.putPiece(3, 0, 'p');
  ASSERT_ANY_THROW( chessGame.movePiece(1, 0, 3, 0););
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(3, 0), 'p');
}

TEST_F(chessBoardTest,blackCantMoveIfIsWhiteTurn){
  chessGame.putPiece(6, 0, 'p');
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 5, 0));
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(5, 0), ' ');
}


TEST_F(chessBoardTest, blackPawnCanNotMoveBackward) {
  chessGame.putPiece(6, 0, 'p');
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 7, 0));
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanMoveOneSquareForward) {
  simpleWhitePawnMove();
  chessGame.putPiece(6, 0, 'p');
  chessGame.movePiece(6, 0, 5, 0);
  ASSERT_EQ(chessGame.getPieceAt(5, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), ' ');
}

TEST_F(chessBoardTest, blackPawnCanMoveTwoSquaresForwardIfIsFirstMove) {
  simpleWhitePawnMove();
  chessGame.putPiece(6, 0, 'p');
  chessGame.movePiece(6, 0, 4, 0);
  ASSERT_EQ(chessGame.getPieceAt(4, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), ' ');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveMoreThan2SquareFoward) {
  simpleWhitePawnMove();
  chessGame.putPiece(6, 0, 'p');
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 3, 0));
  ASSERT_EQ(chessGame.getPieceAt(3, 0), ' ');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveDiagonallyIfIsNotCapturing) {
  simpleWhitePawnMove();
  chessGame.putPiece(6, 0, 'p');
  ASSERT_ANY_THROW(chessGame.movePiece(6, 0, 5, 1));
  ASSERT_EQ(chessGame.getPieceAt(5, 1), ' ');
  ASSERT_EQ(chessGame.getPieceAt(6, 0), 'p');
}

TEST_F(chessBoardTest, blackPawnCanMoveDiagonallyIfIsCapturing) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.putPiece(2, 1, 'p');
  simpleWhitePawnMove();
  chessGame.movePiece(2, 1, 1, 0);
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'p');
  ASSERT_EQ(chessGame.getPieceAt(2, 1), ' ');
}

TEST_F(chessBoardTest, blackPawnCanNotMoveFowardToACellWithAPiece) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.putPiece(2, 0, 'p');
  simpleWhitePawnMove();
  ASSERT_ANY_THROW(chessGame.movePiece(2, 0, 1, 0));
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'p');
}

TEST_F(chessBoardTest, pawnCantJumpOverAPiece) {
  chessGame.putPiece(1, 0, 'P');
  chessGame.putPiece(2, 0, 'p');
  ASSERT_ANY_THROW(chessGame.movePiece(1, 0, 3, 0));
  ASSERT_EQ(chessGame.getPieceAt(1, 0), 'P');
  ASSERT_EQ(chessGame.getPieceAt(2, 0), 'p');
}

TEST_F(chessBoardTest, whitePiecesCantMoveToACellWithAPieceOfTheSameColor){
  chessGame.putPiece(0,0,'R');
  chessGame.putPiece(1,0,'P');
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,1,0));
}

TEST_F(chessBoardTest, blackPiecesCantMoveToACellWithAPieceOfTheSameColor) {
  simpleWhitePawnMove();
  chessGame.putPiece(7, 0, 'r');
  chessGame.putPiece(6, 0, 'p');
  ASSERT_ANY_THROW(chessGame.movePiece(7,0,6,0));
}

TEST_F(chessBoardTest,whiteKnightCanMoveInLShape){
  chessGame.putPiece(0,1,'N');
  chessGame.movePiece(0,1,2,2);
  ASSERT_EQ(chessGame.getPieceAt(2,2),'N');
};

TEST_F(chessBoardTest,blackKnightCanMoveInLShape){
  simpleWhitePawnMove();
  chessGame.putPiece(7,1,'n');
  chessGame.movePiece(7,1,5,2);
  ASSERT_EQ(chessGame.getPieceAt(5,2),'n');
};

TEST_F(chessBoardTest,whiteKnightCanNotMoveInNotLShape){
  chessGame.putPiece(0,1,'N');
  ASSERT_ANY_THROW(chessGame.movePiece(0,1,2,3));
};

TEST_F(chessBoardTest,blackKnightCanNotMoveInNotLShape){
  simpleWhitePawnMove();
  chessGame.putPiece(7,1,'n');
  ASSERT_ANY_THROW(chessGame.movePiece(7,1,2,3));
};

TEST_F(chessBoardTest,bishopCanOnlyMoveDiagonally){
  chessGame.putPiece(0,2,'B');
  ASSERT_ANY_THROW(chessGame.movePiece(0,2,0,4));
  ASSERT_EQ(chessGame.getPieceAt(0,2),'B');
};

TEST_F(chessBoardTest,bishopCantJumpPieces){
  chessGame.putPiece(0,2,'B');
  chessGame.putPiece(1,3,'p');
  ASSERT_ANY_THROW(chessGame.movePiece(0,2,2,4));
  ASSERT_EQ(chessGame.getPieceAt(0,2),'B');
}

TEST_F(chessBoardTest,rookCantMoveDiagonally){
  chessGame.putPiece(0,0,'R');
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,1,1));
  ASSERT_EQ(chessGame.getPieceAt(0,0),'R');
};

TEST_F(chessBoardTest,rookCantJumpPieces){
  chessGame.putPiece(0,0,'R');
  chessGame.putPiece(0,1,'p');
  ASSERT_ANY_THROW(chessGame.movePiece(0,0,0,2));
  ASSERT_EQ(chessGame.getPieceAt(0,0),'R');
}

TEST_F(chessBoardTest,queenCanMoveLikeARook){
  chessGame.putPiece(0,4,'Q');
  chessGame.movePiece(0,4,2,4);
  ASSERT_EQ(chessGame.getPieceAt(2,4),'Q');
};

TEST_F(chessBoardTest,queenCanMoveLikeABishop){
  chessGame.putPiece(0,4,'Q');
  chessGame.movePiece(0,4,4,0);
  ASSERT_EQ(chessGame.getPieceAt(4,0),'Q');
};
TEST_F(chessBoardTest,kingCantMoveMoreThan1SquaresAway){
  ASSERT_ANY_THROW(chessGame.movePiece(0,3,2,3));
  ASSERT_EQ(chessGame.getPieceAt(0,3),'K');
};

TEST_F(chessBoardTest,kingCanMoveOnlyOneSquareInAnyDirection){
  chessGame.movePiece(0,3,1,3);
  ASSERT_EQ(chessGame.getPieceAt(1,3),'K');
}

TEST_F(chessBoardTest,whiteCantMoveAndFinishInCheck){
  chessGame.putPiece(2,3,'q');

  ASSERT_ANY_THROW(chessGame.movePiece(0,3,1,3));
}

TEST_F(chessBoardTest,blackKingCantMoveAndFinishInCheck){
  chessGame.putPiece(5,3,'Q');

  ASSERT_ANY_THROW(chessGame.movePiece(7,3,6,3));
}

TEST_F(chessBoardTest, allPiecesStartCorrectlyWhenStartGame){
  chessGame.startGame();
  for(int i = 0; i < 8; i++){
    ASSERT_EQ(chessGame.getPieceAt(1,i),'P');
    ASSERT_EQ(chessGame.getPieceAt(6,i),'p');
  }
  ASSERT_EQ(chessGame.getPieceAt(0,0),'R');
  ASSERT_EQ(chessGame.getPieceAt(0,1),'N');
  ASSERT_EQ(chessGame.getPieceAt(0,2),'B');
  ASSERT_EQ(chessGame.getPieceAt(0,3),'K');
  ASSERT_EQ(chessGame.getPieceAt(0,4),'Q');
  ASSERT_EQ(chessGame.getPieceAt(0,5),'B');
  ASSERT_EQ(chessGame.getPieceAt(0,6),'N');
  ASSERT_EQ(chessGame.getPieceAt(0,7),'R');

  ASSERT_EQ(chessGame.getPieceAt(7,0),'r');
  ASSERT_EQ(chessGame.getPieceAt(7,1),'n');
  ASSERT_EQ(chessGame.getPieceAt(7,2),'b');
  ASSERT_EQ(chessGame.getPieceAt(7,3),'k');
  ASSERT_EQ(chessGame.getPieceAt(7,4),'q');
  ASSERT_EQ(chessGame.getPieceAt(7,5),'b');
  ASSERT_EQ(chessGame.getPieceAt(7,6),'n');
  ASSERT_EQ(chessGame.getPieceAt(7,7),'r');

  for(int i = 2; i < 6; i++){
    for(int j = 0; j < 8; j++){
      ASSERT_EQ(chessGame.getPieceAt(i,j),' ');
    }
  }
}

TEST_F(chessBoardTest, whitePawnPromotionQueen){
  chessGame.putPiece(6,0,'P');
  chessGame.movePiece(6,0,7,0);
  chessGame.choosePromotion('Q');
  ASSERT_EQ(chessGame.getPieceAt(7,0),'Q');
}

TEST_F(chessBoardTest, whitePawnPromotionKnight){
  chessGame.putPiece(6,0,'P');
  chessGame.movePiece(6,0,7,0);
  chessGame.choosePromotion('N');
  ASSERT_EQ(chessGame.getPieceAt(7,0),'N');
}

TEST_F(chessBoardTest, whitePawnCantPromoteToKingNorPawn){
  chessGame.putPiece(6,0,'P');
  chessGame.movePiece(6,0,7,0);
  ASSERT_ANY_THROW(chessGame.choosePromotion('K'));

}

TEST_F(chessBoardTest, blackPawnPromotion){
  simpleWhitePawnMove();
  chessGame.putPiece(1,0,'p');
  chessGame.movePiece(1,0,0,0);
  chessGame.choosePromotion('Q');
  ASSERT_EQ(chessGame.getPieceAt(0,0),'q');
}


//TEST_F(chessBoardTest, whiteCanCastleKingSide){
//  chessGame.putPiece(0,0,'r');
//  chessGame.movePiece(0,3,0,1);
//  ASSERT_EQ(chessGame.getPieceAt(0,2),'K');
//  ASSERT_EQ(chessGame.getPieceAt(0,3),'R');
//}


