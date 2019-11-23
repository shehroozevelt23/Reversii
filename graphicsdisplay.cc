#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"
#include "grid.h"
#include "cell.h"

GraphicsDisplay::GraphicsDisplay(int g, int w): g{g}, w{w}, x{w,w}{
    x.fillRectangle(0, 0, w, w, Xwindow::Blue);
    
}

void GraphicsDisplay::notify(Subject<Info,State> &who){
    int n = w/g;

    if (who.getInfo().colour == Colour::White){
        x.fillRectangle(n * who.getInfo().col, n * who.getInfo().row, n, n, Xwindow::White);
    }
    else if (who.getInfo().colour == Colour::NoColour){
        x.fillRectangle(n * who.getInfo().col, n * who.getInfo().row, n, n, Xwindow::Blue);
    }
    else if (who.getInfo().colour == Colour::Black){
        x.fillRectangle(n * who.getInfo().col, n * who.getInfo().row, n, n, Xwindow::Black);
    }
}

