#include "policy.hpp"


int MonteCarloPolicy::applyBestMove() {
  vector<vector<int> > board = game->getBoard();
  int scores[4] = {0, 0, 0, 0};
  Game g;

  for (int dir = 0; dir < 4; dir++) {
    for (int i = 0; i < 100; i++) {
      g.setBoard(board);
      scores[dir] += randomPlay(g, dir);
    }
  }

  int maxScore = INT_MIN;
  int maxDir = -1;
  for (int dir = 0; dir < 4; dir++) {
    if (scores[dir] > maxScore) {
      maxScore = scores[dir];
      maxDir = dir;
    }
  }

  cout << "scores: " << scores[0] << " " << scores[1] << " " << scores[2] << " " << scores[3] << endl;

  return game->run(maxDir);
}

int MonteCarloPolicy::randomPlay(Game &g, int dir) {
  while (1 == 1) {
    int res = g.run(dir);
    if (res < 0) {
      break;
    }
    dir = rand() % 4;
  }

  return g.sumBoard();
}