#ifndef __GRAPHICSDISPLAY__
#define __GRAPHICSDISPLAY__
#include "observer.h"
#include "info.h"
#include "window.h"
#include "state.h"

class GraphicsDisplay : public Observer<Info, State> {
	int grid;
	int window;
	Xwindow xw;

	public:
		GraphicsDisplay(int grid, int window);
		void notify(Subject<Info, State> &whoNotified) override;

};
#endif
