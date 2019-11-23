#include "textdisplay.h"
#include "subject.h"
using namespace std;
#include <vector>

TextDisplay::TextDisplay(int n): gridSize{n} {
    
    for (int x = 0; x < n; ++x){
        vector<char> to_add;
        for (int y = 0; y < n; ++y){
                to_add.emplace_back('-');
            
        }

    
        
        theDisplay.emplace_back(to_add);     

    }
    
    
    theDisplay[n/2][n/2] = 'B';
    theDisplay[(n/2) - 1][(n/2) - 1] = 'B';  
    theDisplay[n/2][(n/2) - 1] = 'W';
    theDisplay[(n/2) - 1][n/2] = 'W'; 
    
    
}

void TextDisplay::notify(Subject<Info, State> &whoNotified){
	if(whoNotified.getInfo().colour == Colour::Black){
		theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'B';
	}else if(whoNotified.getInfo().colour == Colour::White){
		theDisplay[whoNotified.getInfo().row][whoNotified.getInfo().col] = 'W';
	}
}

ostream &operator<<(std::ostream &out, const TextDisplay &td){
    for (int x = 0; x < td.gridSize; ++x){
        for (int y = 0; y < td.gridSize; ++y){
            out << td.theDisplay[x][y];
        }
        out << endl;
    }
    return out; 
}
