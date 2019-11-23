#include "grid.h"
#include "graphicsdisplay.h"
#include <vector>
#include "textdisplay.h"
using namespace std;


Grid::~Grid()
{
    delete td;
    delete ob;
}

void Grid::setObserver(Observer<Info, State> *ob)
{
    this->ob = ob;
}

bool Grid::isFull() const
{
    for (unsigned int x = 0; x < theGrid.size(); ++x)
    {
        for (unsigned int y = 0; y < theGrid[x].size(); ++y)
        {
            if (theGrid[x][y].getInfo().colour != Colour::NoColour)
            {
                return false;
            }
        }
    }
    return true;
}

Colour Grid::whoWon() const
{
    int black = 0;
    int white = 0;

    for (unsigned int x = 0; x < theGrid.size(); ++x)
    {
        for (unsigned int y = 0; y < theGrid[x].size(); ++y)
        {
            if (theGrid[x][y].getInfo().colour == Colour::Black)
            {
                ++black;
            }
            else if (theGrid[x][y].getInfo().colour == Colour::White)
            {
                ++white;
            }
        }
    }
    if (black > white)
    {
        return Colour::Black;
    }
    else
    {
        return Colour::White;
    }
}

void neighbour_check(vector<vector<Cell>> &theGrid, int x, int y, int n)
{
    if ((x - 1 >= 0) && (y - 1 >= 0))
    {
        theGrid[x][y].attach(&theGrid[x - 1][y - 1]);
    }
    if ((x - 1 >= 0) && (y >= 0))
    {
        theGrid[x][y].attach(&theGrid[x - 1][y]);
    }
    if ((x - 1 >= 0) && (y + 1 <= n - 1))
    {
        theGrid[x][y].attach(&theGrid[x - 1][y + 1]);
    }

    if ((x >= 0) && (y - 1 >= 0))
    {
        theGrid[x][y].attach(&theGrid[x][y - 1]);
    }

    if ((x >= 0) && (y + 1 <= n - 1))
    {
        theGrid[x][y].attach(&theGrid[x][y + 1]);
    }

    if ((x + 1 <= n - 1) && (y - 1 >= 0))
    {
        theGrid[x][y].attach(&theGrid[x + 1][y - 1]);
    }
    if ((x + 1 <= n - 1) && (y >= 0))
    {
        theGrid[x][y].attach(&theGrid[x + 1][y]);
    }
    if ((x + 1 <= n - 1) && (y + 1 <= n - 1))
    {
        theGrid[x][y].attach(&theGrid[x + 1][y + 1]);
    }

}

void Grid::init(size_t n)
{
    
    theGrid.clear();
    delete td;
    td = new TextDisplay(n);
    ob = new GraphicsDisplay(n, 500);
    

    for (unsigned int x = 0; x < n; ++x)
    {
        vector<Cell> to_add;

        for (unsigned int y = 0; y < n; ++y)
        {

            Cell cell = Cell{x, y};
            cell.attach(ob);

            if (((x == (n / 2) - 1) && (y == (n / 2))) || ((x == (n / 2)) && (y == (n / 2) - 1)))
            {
                cell.setPiece(Colour::White);
            }
            if (((x == (n / 2) - 1) && (y == (n / 2) - 1)) || ((x == (n / 2)) && (y == (n / 2))))
            {
                cell.setPiece(Colour::Black);
            }
            to_add.emplace_back(cell);
        }

        theGrid.emplace_back(to_add);
    }
    setObserver(ob);
    
    for (unsigned int x = 0; x < n; ++x)
    {
        for (unsigned int y = 0; y < n; ++y)
        {
            
            theGrid[x][y].attach(td);
            theGrid[x][y].attach(ob);
            neighbour_check(theGrid, x, y, n);
                       
        }
        
    }
    cout << *td;
}


void Grid::setPiece(size_t r, size_t c, Colour colour)
{
    theGrid[r][c].setPiece(colour);
    cout << *td;
    if (this->isFull() == true)
    {
        if (whoWon() == Colour::Black)
        {
            cout << "Black wins!" << endl;
        }
        else if (whoWon() == Colour::White)
        {
            cout << "White wins!" << endl;
        }
        else
        {
            cout << "Tie!" << endl;
        }
    }
}

void Grid::toggle(size_t r, size_t c)
{
    theGrid[r][c].toggle();
}

ostream &operator<<(std::ostream &out, const Grid &g)
{
    out << *(g.td) << endl;
    return out;
}
