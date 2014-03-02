
#include <X11/Xlib.h>
#include <X11/cursorfont.h>
#include <cstdio>
#include <cstdlib>
class ScreenArea 
{
  private:
    int rx, ry, rw, rh;
  	int btn_pressed, done;
  	int coord[4];

  public:
  	int* TakeArea();
};

int* ScreenArea::TakeArea()
{
	rx = 0;ry = 0;rw = 0;rh = 0;
	btn_pressed = 0; done = 0;

	XEvent ev;
	Display *disp = XOpenDisplay(NULL);

	if(!disp)
		printf("Erro (1)\n");

	Screen *scr = NULL;
	scr = ScreenOfDisplay(disp, DefaultScreen(disp));

	Window root = 0;
	root = RootWindow(disp, XScreenNumberOfScreen(scr));

	Cursor cursor;
	cursor = XCreateFontCursor(disp, XC_left_ptr);

	/* this XGrab* stuff makes XPending true ? */
	if ((XGrabPointer
	   (disp, root, 0,
	    ButtonMotionMask | ButtonPressMask | ButtonReleaseMask, GrabModeAsync,
	    GrabModeAsync, root, cursor, CurrentTime) != GrabSuccess))
	printf("couldn't grab pointer:");

	if ((XGrabKeyboard
	   (disp, root, 0, GrabModeAsync, GrabModeAsync,
	    CurrentTime) != GrabSuccess))
	printf("couldn't grab keyboard:");

	while (!done) {
	while (!done && XPending(disp)) {
	  XNextEvent(disp, &ev);
	  switch (ev.type) {
	    case ButtonPress:
	      btn_pressed = 1;
	      rx = ev.xbutton.x;
	      ry = ev.xbutton.y;
	      break;
	    case ButtonRelease:
	      done = 1;
	      break;
	  }
	}
	}
	rw = ev.xbutton.x - rx;
	rh = ev.xbutton.y - ry;
	/* cursor moves backwards */
	if (rw < 0) {
	rx += rw;
	rw = 0 - rw;
	}
	if (rh < 0) {
	ry += rh;
	rh = 0 - rh;
	}

	XCloseDisplay(disp);
	coord[0]=ry;
	coord[1]=rx;
	coord[2]=rw;
	coord[3]=rh;
	//printf("%dx%d+%d+%d\n",rw,rh,rx,ry);
	return coord;
}