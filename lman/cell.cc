#include "cell.h"
#include "state.h"
#include "subject.h"
#include "observer.h"
#include "info.h"
#include <vector>
#include <cstddef>

//Cell Ctor
Cell::Cell(size_t r, size_t c): r{r}, c{c}, colour{Colour::NoColour}{}

//sets new piece
void Cell::setPiece(Colour colour){
	this->colour = colour;
	State newS{StateType::NewPiece, colour, Direction::N};
	setState(newS);
	notifyObservers();
}

//changes the colour of the cell from black to white or white to black
void Cell::toggle(){
	if(colour == Colour::White){
		colour = Colour::Black;
	}else if(colour == Colour::Black){
		colour = Colour::White;
	}
}

//notifies the change in state
void Cell::notify(Subject<Info, State> &whoFrom){
	if(colour == Colour::NoColour) return;

	int row = whoFrom.getInfo().row;
	int col = whoFrom.getInfo().col;
	Colour colour = whoFrom.getState().colour;
	StateType type = whoFrom.getState().type;
	Direction FromDir = whoFrom.getState().direction;
	Direction dir;

	if((col == c) && (row < r)) dir = Direction::N;
	if((col == c) && (row > r)) dir = Direction::S;
	if((row == r) && (col < c)) dir = Direction::W;
	if((row == r) && (col > c)) dir = Direction::E;
	if((col < c) && (row < r)) dir = Direction::NW;
	if((col > c) && (row < r)) dir = Direction::NE;
	if((col > c) && (row > r)) dir = Direction::SE;
	if((col < c) && (row > r)) dir = Direction::SW;

	//notification if a new piece is added
	if(type == StateType::NewPiece){		
	
		if(this->colour != colour){
			State newS{StateType::Relay, colour, dir};
			setState(newS);
			notifyObservers();
			return;
		}
		return;
	//notification if relaying a message
	}else if(type == StateType::Relay){
		if(dir == FromDir){
			if(this->colour != colour){
				setState(whoFrom.getState());
				notifyObservers();
				return;
			}
			State newS{StateType::Reply, colour, Direction::S};
			if(FromDir == Direction::N)  newS = {StateType::Reply, colour, Direction::S};
			if(FromDir == Direction::S)  newS = {StateType::Reply, colour, Direction::N};
			if(FromDir == Direction::E)  newS = {StateType::Reply, colour, Direction::W};
			if(FromDir == Direction::W)  newS = {StateType::Reply, colour, Direction::E};
			if(FromDir == Direction::NE)  newS = {StateType::Reply, colour, Direction::SW};
			if(FromDir == Direction::SW)  newS = {StateType::Reply, colour, Direction::NE};
			if(FromDir == Direction::NW)  newS = {StateType::Reply, colour, Direction::SE};
			if(FromDir == Direction::SE)  newS = {StateType::Reply, colour, Direction::NW};
			
			setState(newS);
			notifyObservers();
		}
		return;
	//notification if replying 
	}else if(type == StateType::Reply){
		if((dir == FromDir) && (this->colour != colour)){
			toggle();
			State newS{StateType::Reply, colour, FromDir};
			setState(newS);
			notifyObservers();
		}
		return;
	}
}

// Gives info of the cell
Info Cell::getInfo() const{
	Info retval{r, c, colour};
	return retval;
}

