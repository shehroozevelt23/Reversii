#include "grid.h"
#include "cell.h"
#include "state.h"
#include "info.h"
#include <vector>
#include <iostream>
#include <cstddef>
#include "textdisplay.h"
#include "graphicsdisplay.h"
using namespace std;

//dtor of Grid
Grid::~Grid(){
	delete td;
	delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob){
	for(auto &i : theGrid){
		for(auto &j : i){
			j.attach(ob);
		}
	}
}

//initializes a grid and neighbours of each cell
void Grid::init(size_t n){
	delete ob;
	delete td;
	td = new TextDisplay(n);
	ob = new GraphicsDisplay(n, 500);
	theGrid.clear();
	
	//filling the grid with cells
	for(size_t i = 0; i < n; i++){
		vector <Cell> row;
		for(size_t j = 0; j < n; j++){
			Cell cell = {i, j};
			row.emplace_back(cell);
		}
		theGrid.emplace_back(row);
	}
	setObserver(ob);	
	//attaching neighbours
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			theGrid[i][j].attach(td); 
			for(int row = i - 1; row <= i + 1; row++){
				for(int col = j - 1; col <= j + 1; col++){
					if((row > -1) && (row < n) && (col > -1) && (col < n)){
						if(!(row == i) || !(col == j)){
							theGrid[i][j].attach(&theGrid[row][col]);
						}
					}
				}
			}
		}
	}
	int mid = n/2;
	theGrid[mid][mid].setPiece(Colour::Black);
	theGrid[mid - 1][mid].setPiece(Colour::White);
	theGrid[mid][mid - 1].setPiece(Colour::White);
	theGrid[mid - 1][mid - 1].setPiece(Colour::Black);
}

//checks if the grid is full
bool Grid::isFull() const{
	for(int i = 0; i < theGrid.size(); i++){
		for(int j = 0; j < theGrid.size(); j++){
			if(theGrid[i][j].getInfo().colour == Colour::NoColour){
				return false;
			}
		}
	}
	return true;
}

//returns the colour of the winner or noColour if tied
Colour Grid::whoWon() const{
	int countBlack = 0;
	int countWhite = 0;
	for(int i = 0; i < theGrid.size(); i++){
		for(int j = 0; j < theGrid.size(); j++){
			if(theGrid[i][j].getInfo().colour == Colour::Black){
				countBlack++;
			}
			if(theGrid[i][j].getInfo().colour == Colour::White){
				countWhite++;
			}
		}
	}
	if(countBlack > countWhite){
		return Colour::Black;
	}
	if(countWhite > countBlack){
		return Colour::White;
	}
	return Colour::NoColour;
}

//sets the cell at r and c with the given colour
void Grid::setPiece(size_t r, size_t c, Colour colour){
	if((r <= theGrid.size()) && (c <= theGrid.size()) && (theGrid[r][c].getInfo().colour == Colour::NoColour)){
		theGrid[r][c].setPiece(colour);
	}else{
		throw 1;
	}
}

//changes the colour of the cell at r and c from black to white or white to black
void Grid::toggle(size_t r, size_t c){
	theGrid[r][c].toggle();
}

//output operator for Grid
std::ostream &operator<<(std::ostream &out, const Grid &g){
	out << *(g.td);
	return out;
}

