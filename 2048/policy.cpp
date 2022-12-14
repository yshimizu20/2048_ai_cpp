#include "policy.hpp"


Policy::Policy() {
  cout << "Policy created" << endl;
}

void Policy::play() {
  while (1 == 1) {
    int res = applyBestMove();
    if (res < 0) {
      game->printBoard();
      cout << "game over" << endl;
      return;
    }
    game->printBoard();
  }
}

int evalEmptyCells(vector<vector<int> > &board) {
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

int evalSteadyIncrement(vector<vector<int> > &board) {
  int leftright = 0, updown = 0;

  for (int i = 0; i < 4; i++) {
    int left = 0, right = 0;
    int conseq1 = 0, conseq2 = 0;

    for (int j = 0; j < 3; j++) {
      if (board[i][j] < board[i][j+1]) {
        right += board[i][j+1];
        conseq1++;
        conseq2 = 0;
        left -= pow(conseq1, 2) * 3;
      } else if (board[i][j] > board[i][j+1]) {
        left += board[i][j];
        conseq1 = 0;
        conseq2++;
        right -= pow(conseq2, 2) * 3;
      } else {
        conseq1++;
        conseq2++;
        left -= pow(conseq1, 2) * 3;
        right -= pow(conseq2, 2) * 3;
      }
      leftright -= min(left, right);
    }
  }

  for (int j = 0; j < 4; j++) {
    int up = 0, down = 0;
    int conseq1 = 0, conseq2 = 0;

    for (int i = 0; i < 3; i++) {
      if (board[i][j] < board[i+1][j]) {
        up += board[i+1][j];
        conseq1++;
        conseq2 = 0;
        down -= pow(conseq1, 2) * 3;
      } else if (board[i][j] > board[i+1][j]) {
        down += board[i][j];
        conseq2++;
        conseq1 = 0;
        up -= pow(conseq2, 2) * 3;
      } else {
        conseq1++;
        conseq2++;
        up -= pow(conseq2, 2) * 3;
        down -= pow(conseq1, 2) * 3;
      }
      updown -= min(up, down);
    }
  }

  return leftright + updown;
}

int evalProximity(vector<vector<int> > &board) {
  int proximity = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      int minProx = INT_MAX;
      if (i)
        minProx = min(minProx, abs(board[i][j] - board[i-1][j]));
      if (i < 3)
        minProx = min(minProx, abs(board[i][j] - board[i+1][j]));
      if (j)
        minProx = min(minProx, abs(board[i][j] - board[i][j-1]));
      if (j < 3)
        minProx = min(minProx, abs(board[i][j] - board[i][j+1]));
      proximity += minProx;
    }
  }
  return -proximity;
}
