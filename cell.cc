#include "cell.h"
#include "state.h"
#include "subject.h"
#include <iostream>
using namespace std;

Cell::Cell(size_t r, size_t c) : r{r}, c{c} {}

void Cell::setPiece(Colour colour)
{
    this->colour = colour;
    this->setState({StateType::NewPiece, colour});
    this->notifyObservers();
}

void Cell::toggle()
{
    if (colour == Colour::Black)
    {
        colour = Colour::White;
    }
    else if (colour == Colour::White)
    {
        colour = Colour::Black;
    }
}

Direction reverse(int row, int col, int other_col, int other_row)
{
    if ((col > other_col) && (row == other_row))
    {
        return Direction::W;
    }
    else if ((col > other_col) && (row > other_row))
    {
        return Direction::NW;
    }
    else if ((col > other_col) && (row < other_row))
    {
        return Direction::SW;
    }
    else if ((col == other_col) && (row > other_row))
    {
        return Direction::N;
    }
    else if ((col == other_col) && (row < other_row))
    {
        return Direction::S;
    }
    else if ((col < other_col) && (row == other_row))
    {
        return Direction::E;
    }
    else if ((col < other_col) && (row < other_row))
    {
        return Direction::SE;
    }
    else
    {
        return Direction::NE;
    }
}

Direction direction(int row, int col, int other_col, int other_row)
{
    if ((col > other_col) && (row == other_row))
    {
        return Direction::E;
    }
    else if ((col > other_col) && (row > other_row))
    {
        return Direction::SE;
    }
    else if ((col > other_col) && (row < other_row))
    {
        return Direction::NE;
    }
    else if ((col == other_col) && (row > other_row))
    {
        return Direction::S;
    }
    else if ((col == other_col) && (row < other_row))
    {
        return Direction::N;
    }
    else if ((col < other_col) && (row == other_row))
    {
        return Direction::W;
    }
    else if ((col < other_col) && (row < other_row))
    {
        return Direction::NW;
    }
    else
    {
        return Direction::SW;
    }
}


void Cell::notify(Subject<Info, State> &whoFrom)
{

    if (whoFrom.getState().type == StateType::Reply)
    {
        
            if (Colour::NoColour != colour && whoFrom.getState().colour != colour)
            {
                
                Direction dir = direction(getInfo().row, getInfo().col, whoFrom.getInfo().col, whoFrom.getInfo().row);
                if (dir == whoFrom.getState().direction){
                    State s{StateType::Reply, whoFrom.getState().colour, whoFrom.getState().direction};
                    this->setState(s);
                    this->toggle();
                    this->notifyObservers();
                }
            }
        
    }

    else if (whoFrom.getState().type == StateType::NewPiece)
    {
    
        
            if (Colour::NoColour != colour && whoFrom.getState().colour != colour)
            {
    
                Direction dir = direction(getInfo().row, getInfo().col, whoFrom.getInfo().col, whoFrom.getInfo().row);
                State s{StateType::Relay, whoFrom.getState().colour, dir};
                this->setState(s);
                this->notifyObservers();
            }
        
    }
    else
    {
            Direction dir = direction(getInfo().row, getInfo().col, whoFrom.getInfo().col, whoFrom.getInfo().row);
            if (whoFrom.getState().direction == dir)
            {
                if (Colour::NoColour != colour)
                {
                    if (colour == whoFrom.getInfo().colour)
                    {
                        State s{StateType::Relay, whoFrom.getState().colour, whoFrom.getState().direction};
                        this->setState(s);
                        this->notifyObservers();
                    }
                    else
                    {
                        Direction rev = reverse(getInfo().row, getInfo().col, whoFrom.getInfo().col, whoFrom.getInfo().row);
                        State s{StateType::Reply, whoFrom.getState().colour, rev};
                        this->setState(s);
                        this->notifyObservers();
                    }
                }
            }
    }
    

}

Info Cell::getInfo() const
{
    Info i;
    i.row = r;
    i.col = c;
    i.colour = colour;
    return i;
}




