#include <iostream>
#include <string>

using namespace std;

#include "Chess.h"

void parseMove(string &move){
  string temp = move;
  move[0] = temp[1]-1;
  move[1] = temp[0]-'a'+'0';
  move[2] = temp[3]-1;
  move[3] = temp[2]-'a'+ '0';
}

int main(){

  char initialPieces[8][8] = {
          {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'},
          {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
          {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
          {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'}
  };
  Chess chessGame;
  chessGame = Chess();
  chessGame.startGame(initialPieces);

  while(chessGame.isGameRunning()){
    chessGame.printBoard();
    cout << "Enter move: ";
    string move;
    cin >> move;
    if(move == "exit"){
      break;
    }
    parseMove(move);
    try {
      chessGame.movePiece(move[0]-'0', move[1]-'0', move[2]-'0', move[3]- '0');
    } catch (invalid_argument &e) {
      cout << "Invalid move" << endl;
      cout << e.what() << endl;
      cout<< "Try again" << endl;
    }


  }
  cout<< "Game over" << endl;
  return 0;
}