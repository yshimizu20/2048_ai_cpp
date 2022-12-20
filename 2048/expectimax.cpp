#include "policy.hpp"
#include <iostream>

using namespace std;


int main(void) {
  Game* g = new Game();
  char userInput;
  int response;

  cin >> userInput;
  if (userInput == 'p') {
    // Policy *p = new MonteCarloPolicy();
    Policy *p = new ExpectimaxPolicy();
    p->play();
    cout << "game over" << endl;
    return 0;
  }
  g->printBoard();
  while (userInput != 'q') {
    if (userInput == 'w') {
      response = g->run(3);
    } else if (userInput == 'a') {
      response = g->run(2);
    } else if (userInput == 's') {
      response = g->run(1);
    } else if (userInput == 'd') {
      response = g->run(0);
    }
    if (response >= 0) {
      g->printBoard();
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