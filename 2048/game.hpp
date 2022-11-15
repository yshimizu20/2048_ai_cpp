#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;


class Game {
private:
  vector<vector<int> > mainBoard;
  int score;
  int win;

public:
  Game(int target);

  void printBoard();
  void addTile();
  int move(vector<vector<int> >& board, string direction);
  int moveRight(vector<vector<int> > &board);
  int mergeRight(vector<vector<int> > &board);
  bool pushRight(vector<vector<int> > &board);
  void rotateRight(vector<vector<int> > &board);
  void rotateLeft(vector<vector<int> > &board);
  void rotate180(vector<vector<int> > &board);
  int getScore() const { return score; };
  bool checkWin();
};