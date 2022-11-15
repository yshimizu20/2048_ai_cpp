#include "game.hpp"


Game::Game(int target) {
  win = target;
  mainBoard = vector<vector<int> >(4, vector<int>(4, 0));

  addTile(mainBoard);
  addTile(mainBoard);
}

void Game::printBoard() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      cout << mainBoard[i][j] << " ";
    }
    cout << endl;
  }
}

bool Game::addTile(vector<vector<int> > &board) {
  vector<int> emptyTiles;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (board[i][j] == 0) {
        emptyTiles.push_back(i * 4 + j);
      }
    }
  }

  if (emptyTiles.size() == 0) {
    return false;
  }

  int index = rand() % emptyTiles.size();
  int row = emptyTiles[index] / 4;
  int col = emptyTiles[index] % 4;

  board[row][col] = (rand() % 10 == 0) ? 4 : 2;

  return true;
}

int Game::run(string direction) {
  int points = move(mainBoard, direction);
  if (points >= 0) {
    addTile(mainBoard);
  }
  return points;
}

int Game::move(vector<vector<int> >& board, string direction) {
  int ret;

  if (direction == "right") {
    ret = moveRight(board);
  } else if (direction == "left") {
    rotate180(board);
    ret = moveRight(board);
    rotate180(board);
  } else if (direction == "down") {
    rotateLeft(board);
    ret = moveRight(board);
    rotateRight(board);
  } else if (direction == "up") {
    rotateRight(board);
    ret = moveRight(board);
    rotateLeft(board);
  } else {
    cout << "Invalid direction" << endl;
    return -2;
  }

  return ret;
}

int Game::moveRight(vector<vector<int> > &board) {
  bool isChanged = false;
  int ret;

  printBoard();
  isChanged |= pushRight(board);
  printBoard();
  ret = mergeRight(board);
  printBoard();
  isChanged |= pushRight(board);
  printBoard();

  cout << isChanged << endl;
  cout << ret << endl;

  if (ret == -1 && !isChanged) {
    return -1;
  } else {
    return ret;
  }
}

int Game::mergeRight(vector<vector<int> > &board) {
  int ret = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 3; j > 0; j--) {
      if (board[i][j] == board[i][j-1] && board[i][j] != 0) {
        board[i][j] *= 2;
        board[i][j-1] = 0;
        ret += board[i][j];
      }
    }
  }

  return ret;
}

bool Game::pushRight(vector<vector<int> > &board) {
  bool isChanged = false;

  for (int i = 0; i < 4; i++) {
    int idx = 3;
    for (int j = 3; j >= 0; j--) {
      if (board[i][j] != 0) {
        board[i][idx] = board[i][j];
        if (j != idx) {
          board[i][j] = 0;
          isChanged = true;
        }
        idx--;
      }
    }
  }

  return isChanged;
}

void Game::rotateRight(vector<vector<int> > &board) {
  vector<vector<int> > tempBoard = board;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      board[i][j] = tempBoard[3-j][i];
    }
  }
}

void Game::rotateLeft(vector<vector<int> > &board) {
  vector<vector<int> > tempBoard = board;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      board[i][j] = tempBoard[j][3-i];
    }
  }
}

void Game::rotate180(vector<vector<int> > &board) {
  vector<vector<int> > tempBoard = board;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      board[i][j] = tempBoard[3-i][3-j];
    }
  }
}

bool Game::checkWin() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (mainBoard[i][j] >= win) {
        return true;
      }
    }
  }
  return false;
}