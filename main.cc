#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;
  int turn = 0;

  // Add code here


  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      if ((n%2 == 0) && (n > 3)){
        g.init(n);
      }
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      if (turn % 2 == 0){
        g.setPiece(r, c, Colour::Black);
        ++turn;
      }
      else{
        g.setPiece(r, c, Colour::White);
        ++turn;
      }
    }
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
