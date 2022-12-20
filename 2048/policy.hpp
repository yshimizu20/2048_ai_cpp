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

  virtual int applyBestMove() = 0;
  virtual float evalBoard(vector<vector<int> > &board) = 0;
  // virtual pair<int, float> bestMove(vector<vector<int> > &board, int depth, float prob) = 0;
};

/*
  * ExpectimaxPolicy
  * 
  * This policy evaluates every possible stochastic outcomes for each state for a certain depth and returns the best move.
  * 
  * It uses a depth of 3 and a heuristic function to evaluate the board.
*/
class ExpectimaxPolicy : public Policy {
public:
  ExpectimaxPolicy() : Policy() {
    cout << "ExpectimaxPolicy created" << endl;
  }

  int applyBestMove();
  pair<int, float> bestMove(vector<vector<int> > &board, int depth, float prob);
  float minOfPossibleMoves(vector<vector<int> > &board, int depth, float prob);
  float evalBoard(vector<vector<int> > &board);
};

/*
 * MCTSPolicy <- did not work
 *
 * This policy evaluates the best move using the Monte Carlo Tree Search algorithm.
 *
 * It uses a depth of 8 with 500 iterations, and a heuristic function to evaluate the board.
*/

/*
 * Monte Carlo Policy
 *
 * Run 500 iterations of moves starting from the given state and return the best move
*/
class MonteCarloPolicy : public Policy {
public:
  MonteCarloPolicy() : Policy() {
    cout << "MonteCarloPolicy created" << endl;
  }

  int applyBestMove();
  int randomPlay(Game &g, int dir);
  float evalBoard(vector<vector<int> > &board) { return 0; }
};

int evalEmptyCells(vector<vector<int> > &board);
int evalSteadyIncrement(vector<vector<int> > &board);
int evalProximity(vector<vector<int> > &board);