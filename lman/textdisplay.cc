#include "textdisplay.h"
#include <iostream>
#include <vector>
#include "observer.h"
#include "state.h"
#include "info.h"
#include "subject.h"
#include "cell.h"
using namespace std;

TextDisplay::TextDisplay(int n): gridSize{n}{
	

	for(int i = 0; i < gridSize; i++){
		vector<char> c;
		for(int j = 0; j < gridSize; j++){
			char sym = '-';
			c.emplace_back(sym);
		}
		theDisplay.emplace_back(c);
	}

}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
	if(whoNotified.getInfo().colour == Colour::Black){
		theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
	}else if(whoNotified.getInfo().colour == Colour::White){
		theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
	}
}

std::ostream &operator<<(std::ostream &out, const TextDisplay &td){
	for(int i = 0; i < td.theDisplay.size(); i++){
		for(int j = 0; j < td.theDisplay.size(); j++){
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
}
