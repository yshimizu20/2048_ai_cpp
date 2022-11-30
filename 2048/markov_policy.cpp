#include "policy.hpp"

int MarkovDecisionPolicy::applyBestMove() {
  vector<vector<int> > board = game->getBoard();
  int direction = bestMove(board, 3, 1.0).first;

  return game->run(direction);
}

pair<int, float> MarkovDecisionPolicy::bestMove(vector<vector<int> > &board, int depth, float prob) {
  float bestScore = INT_MIN;
  int bestDirection = 0;

  for (int dir = 0; dir < 4; dir++) {
    vector<vector<int> > newBoard = board;
    int points = Policy::game->move(newBoard, dir);

    if (points >= 0) {
      float score = minOfPossibleMoves(newBoard, depth - 1, prob) + points;
      if (score > bestScore) {
        bestScore = score;
        bestDirection = dir;
      }
    }
  }

  return make_pair(bestDirection, bestScore);
}

float MarkovDecisionPolicy::minOfPossibleMoves(vector<vector<int> > &board, int depth, float prob) {
  if (depth == 0) {
    return evalBoard(board);
  }
  vector<float> scores;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j])
        continue;
      
      int score = 0;
      for (int dice : {2, 4}) {
        for (float ratio : {0.9, 0.1}) {
          vector<vector<int>> newBoard = board;
          newBoard[i][j] = dice;
          score += bestMove(newBoard, depth, prob * ratio).second * ratio;
        }
      }
      scores.push_back(score);
    }
  }

  // return average of scores
  float sum = 0;
  for (float score : scores)
    sum += score;
  
  return sum / scores.size();
}

float MarkovDecisionPolicy::evalBoard(vector<vector<int> > &board) {
  int emptyCells = evalEmptyCells(board);
  int proximity = evalProximity(board);
  int steadyIncrement = evalSteadyIncrement(board);

  return float(steadyIncrement * 3 - pow(16 - emptyCells, 2) + proximity);
}