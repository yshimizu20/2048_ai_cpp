#include<vector>
#include<stdlib.h>
#include "game.hpp"

class Policy {
private:
  Game game;

public:
  Policy(Game g);

  void play();
  void applyBestMove();
  pair<int, float> bestMove(vector<vector<int> > &board, int depth, float prob);
  float minOfPossibleMoves(vector<vector<int> > &board, int depth, float prob);
  float evalBoard(vector<vector<int> > &board);
};

int evaluateEmptyCells(vector<vector<int> > &board);
int evaluateSteadyIncrement(vector<vector<int>> &board);
int evaluateProximity(vector<vector<int>> &board);