#include "game.hpp"
#include "policy.hpp"
#include <iostream>

using namespace std;


int main(void) {
  Game g(2048);
  char userInput;
  int response;

  g.printBoard();
  cin >> userInput;
  if (userInput == "ai") {
    Policy p(g);
    p.play();
    cout << "game over" << endl;
    return 0;
  }
  while (userInput != 'q') {
    if (userInput == 'w') {
      response = g.run(3);
    } else if (userInput == 'a') {
      response = g.run(2);
    } else if (userInput == 's') {
      response = g.run(1);
    } else if (userInput == 'd') {
      response = g.run(0);
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