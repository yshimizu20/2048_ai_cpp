#include "policy.hpp"


Policy::Policy(Game g) {
  game = g;
}

void Policy::play() {
  while (!game.checkWin()) {
    applyBestMove();
  }
}

void Policy::applyBestMove() {
  vector<vector<int> > board = game.getBoard();
  int direction = bestMove(board, 4, 1.0).first;

  game.run(direction);
}

pair<int, float> Policy::bestMove(vector<vector<int> > &board, int depth, float prob) {
  float bestScore = -1;
  int bestDirection = 0;

  for (int dir = 0; dir < 4; dir++) {
    vector<vector<int> > newBoard = board;
    int points = game.move(newBoard, dir);

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

float Policy::minOfPossibleMoves(vector<vector<int> > &board, int depth, float prob) {
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

float Policy::evalBoard(vector<vector<int> > &board) {
  int emptyCells = evalEmptyCells(board);
  int proximity = evalProximity(board);
  int steadyIncrement = evalSteadyIncrement(board);

  return float(emptyCells + proximity + steadyIncrement);
}

int evaluateEmptyCells(vector<vector<int> > &board) {
  int emptyCells = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) {
        emptyCells++;
      }
    }
  }
  return emptyCells;
}

int evaluateSteadyIncrement(vector<vector<int> > &board) {
  int leftright = 0, updown = 0;

  for (int i = 0; i < 4; i++) {
    int left = 0, right = 0;
    for (int j = 0; j < 3; j++) {
      if (board[i][j] < board[i][j+1]) {
        left += board[i][j+1];
      } else if (board[i][j] > board[i][j+1]) {
        right += board[i][j];
      }
    }
    leftright = min(left, right);
  }

  for (int j = 0; j < 4; j++) {
    int up = 0, down = 0;
    for (int i = 0; i < 3; i++) {
      if (board[i][j] < board[i+1][j]) {
        up += board[i+1][j];
      } else if (board[i][j] > board[i+1][j]) {
        down += board[i][j];
      }
    }
    updown += min(up, down);
  }

  return leftright + updown;
}

int evaluateProximity(vector<vector<int> > &board) {
  int proximity = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int minProx = INT_MAX;
      if (i) {
        minProx = min(minProx, abs(board[i][j] - board[i-1][j]));
      }
      if (i < 3) {
        minProx = min(minProx, abs(board[i][j] - board[i+1][j]));
      }
      if (j) {
        minProx = min(minProx, abs(board[i][j] - board[i][j-1]));
      }
      if (j < 3) {
        minProx = min(minProx, abs(board[i][j] - board[i][j+1]));
      }
      proximity += minProx;
    }
  }
  return proximity;
}