/**
 * C++ class for a game of the Tower of Hanoi puzzle.
 * 
 * @author
 *   Wade Fagen-Ulmschneider <waf@illinois.edu>
 */

#include "Game.h"
#include "Stack.h"
#include "uiuc/Cube.h"
#include "uiuc/HSLAPixel.h"
#include <iostream>
using std::cout;
using std::endl;

// Solves the Tower of Hanoi puzzle.
// (Feel free to call "helper functions" to help you solve the puzzle.)
void Game::solve() {
  bool moveRight = true;
  while (stacks_[2].size() != 4) {
    if (moveRight == true) {
        _smallestRight();
    } else {
        _nextLegal();
    }

    moveRight = !moveRight;

    cout << *this << endl;
  }
}

void Game::_smallestRight() {
  for (int i = 0; i < 3; i++) {
      if (stacks_[i].size() > 0) {
          if (stacks_[i].peekTop().getLength() == 1) {
              int next = i == 2 ? 0 : i + 1;
              stacks_[next].push_back(stacks_[i].removeTop());
              return;
          }
      }
  }
}

void Game::_nextLegal() {
  int smallest = 0;
  for (int i = 0; i < 3; i++) {
      if (stacks_[i].size() > 0) {
          if (stacks_[i].peekTop().getLength() == 1) {
              smallest = i;
          }
      }
  }
  
  Stack & stackA = stacks_[(smallest + 1) % 3];
  Stack & stackB = stacks_[(smallest + 2) % 3];
  bool moveRight = true;
  if  (stackA.size() > 0 && stackB.size() > 0) {
     moveRight = stackB.peekTop().getLength() > stackA.peekTop().getLength();
  } else if (stackA.size() > 0) {
      moveRight = true;
  } else {
      moveRight = false;
  }

  if (moveRight == true) {
      stackB.push_back(stackA.removeTop());
  } else {
      stackA.push_back(stackB.removeTop());
  }
}

// Default constructor to create the initial state:
Game::Game() {
  // Create the three empty stacks:
  for (int i = 0; i < 3; i++) {
    Stack stackOfCubes;
    stacks_.push_back( stackOfCubes );
  }

  // Create the four cubes, placing each on the [0]th stack:
  Cube blue(4, uiuc::HSLAPixel::BLUE);
  stacks_[0].push_back(blue);

  Cube orange(3, uiuc::HSLAPixel::ORANGE);
  stacks_[0].push_back(orange);

  Cube purple(2, uiuc::HSLAPixel::PURPLE);
  stacks_[0].push_back(purple);

  Cube yellow(1, uiuc::HSLAPixel::YELLOW);
  stacks_[0].push_back(yellow);
}

std::ostream& operator<<(std::ostream & os, const Game & game) {
  for (unsigned i = 0; i < game.stacks_.size(); i++) {
    os << "Stack[" << i << "]: " << game.stacks_[i];
  }
  return os;
}
