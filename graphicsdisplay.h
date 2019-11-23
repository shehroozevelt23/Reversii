#ifndef __GDISPLAY__
#define __GDISPLAY__
#include "observer.h"
#include "info.h"
#include "window.h"
#include "state.h"

class GraphicsDisplay : public Observer<Info, State> {
	int g;
	int w;
	Xwindow x;

	public:
		GraphicsDisplay(int g, int w);
		void notify(Subject<Info, State> &whoNotified) override;

};
#endif
