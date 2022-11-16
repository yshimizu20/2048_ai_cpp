#include<vector>
#include<stdlib.h>
#include<climits>
#include<math.h>
#include "game.hpp"

class Policy {
private:
  Game* game = new Game();

public:
  Policy();

  void play();
  int applyBestMove();
  pair<int, float> bestMove(vector<vector<int> > &board, int depth, float prob);
  float minOfPossibleMoves(vector<vector<int> > &board, int depth, float prob);
  float evalBoard(vector<vector<int> > &board);
};

int evalEmptyCells(vector<vector<int> > &board);
int evalSteadyIncrement(vector<vector<int>> &board);
int evalProximity(vector<vector<int>> &board);