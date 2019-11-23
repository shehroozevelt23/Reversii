#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "grid.h"
#include "state.h"
#include "graphicsdisplay.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  // Add code here
  bool player1 = true;
  try {
  while (true) {
    cin >> cmd;
    if (cmd == "new") {
      int n;
      cin >> n;
      // Add code here
      if((n >= 4) && !(n % 2)){
        g.init(n);
        cout << g;
        player1 = true;
      }
      continue;
    }
    else if (cmd == "play") {
      int r = 0, c = 0;
      cin >> r >> c;
      // Add code here
      try{
	      if(player1){
		      g.setPiece(r, c, Colour::Black);
	      }else{
		      g.setPiece(r, c, Colour::White);
	      }
      }catch(int m){
	continue;
      }
      cout << g;
    }
    if(g.isFull()){
	if(g.whoWon() == Colour::Black){
		cout << "Black Wins!" << endl;
	}else if(g.whoWon() == Colour::White){
		cout << "White Wins!" << endl;
	}else{
		cout << "Tie!" << endl;
	}
	break;
    }
    player1 = !(player1);
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}
