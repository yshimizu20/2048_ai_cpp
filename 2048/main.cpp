#include "game.hpp"
#include <iostream>

using namespace std;


int main(void) {
  Game g(2048);
  char userInput;
  int response;

  g.printBoard();
  cin >> userInput;
  while (userInput != 'q') {
    if (userInput == 'w') {
      response = g.run("up");
    } else if (userInput == 'a') {
      response = g.run("left");
    } else if (userInput == 's') {
      response = g.run("down");
    } else if (userInput == 'd') {
      response = g.run("right");
    }
    if (response >= 0) {
      g.printBoard();
    } else if (response == -1) {
      cout << "game over" << endl;
      return 0;
    } else {
      cout << "invalid move" << endl;
    }
    cin >> userInput;
  }

  return 0;
}