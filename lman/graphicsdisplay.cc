#include "graphicsdisplay.h"
#include "info.h"
#include "subject.h"

GraphicsDisplay::GraphicsDisplay(int grid, int window):
	grid{grid}, window{window}, xw{window, window} {
		xw.fillRectangle(0, 0, window, window, Xwindow::Blue);
	}

void GraphicsDisplay::notify(Subject<Info, State> &whoNotified){
	int size = window/grid;

	if(whoNotified.getInfo().colour == Colour::Black){
		xw.fillRectangle(whoNotified.getInfo().col * size, whoNotified.getInfo().row * size, size, size, Xwindow::Black);
	}else if(whoNotified.getInfo().colour == Colour::White){
		xw.fillRectangle(whoNotified.getInfo().col * size, whoNotified.getInfo().row * size, size, size, Xwindow::White);

	}else{
		xw.fillRectangle(whoNotified.getInfo().col * size, whoNotified.getInfo().row * size, size, size, Xwindow::Blue);
	}
}
