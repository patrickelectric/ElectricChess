/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

Display *display = XOpenDisplay(NULL);
Window root = DefaultRootWindow(display);

Mat ScreenShot();
Mat XImage2MatImageAdapter(XImage *ximage);

Mat ScreenShot()
{
  XWindowAttributes gwa;

  XGetWindowAttributes(display, root, &gwa);
  int width = gwa.width;
  int height = gwa.height;
  XDestroyWindow(display,root);


  return XImage2MatImageAdapter(XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap));  
}

Mat XImage2MatImageAdapter(XImage *ximage)
{
  IplImage *iplImage;
  assert(ximage->format == ZPixmap);
  assert(ximage->depth == 24); 

  iplImage = cvCreateImageHeader(
                cvSize(ximage->width, ximage->height), 
                IPL_DEPTH_8U,
                ximage->bits_per_pixel/8);

  iplImage->widthStep = ximage->bytes_per_line;
  if(ximage->data != NULL)
    iplImage->imageData = ximage->data;
	
  Mat imgmat(iplImage,false);
  return imgmat;
};