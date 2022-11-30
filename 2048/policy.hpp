#include<vector>
#include<stdlib.h>
#include<climits>
#include<math.h>
#include "game.hpp"

class Policy {
protected:
  Game* game = new Game();

public:
  Policy();

  void play();
  int applyBestMove();

  virtual pair<int, float> bestMove(vector<vector<int> > &board, int depth, float prob) = 0;
  virtual float evalBoard(vector<vector<int> > &board) = 0;
};

class ExtensivePolicy : public Policy {
public:
  ExtensivePolicy() : Policy() {
    cout << "ExtensivePolicy created" << endl;
  }

  pair<int, float> bestMove(vector<vector<int>> &board, int depth, float prob);
  float minOfPossibleMoves(vector<vector<int>> &board, int depth, float prob);
  float evalBoard(vector<vector<int> > &board);
};

// class MonteCarloTreeSearchPolicy : public Policy {
// public:
//   MonteCarloTreeSearchPolicy() : Policy() {
//     cout << "MonteCarloTreeSearchPolicy created" << endl;
//   }
  
//   float evalBoard(vector<vector<int> > &board);
// };

int evalEmptyCells(vector<vector<int> > &board);
int evalSteadyIncrement(vector<vector<int>> &board);
int evalProximity(vector<vector<int>> &board);