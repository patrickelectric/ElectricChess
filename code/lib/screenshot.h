/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

class ScreenImage 
{
  private:
    Display *display;
    Window window;

    Mat XImage2MatImageAdapter(XImage *ximage);
  public:
    Mat ScreenShot();
    void ScreenInit();
};

void ScreenImage::ScreenInit()
{
  display = XOpenDisplay(NULL);
  window = DefaultRootWindow(display);
}

Mat ScreenImage::ScreenShot()
{
  XWindowAttributes gwa;
  XGetWindowAttributes(display, window, &gwa);
  return XImage2MatImageAdapter(XGetImage(display,window, 0,0 , gwa.width,gwa.height,AllPlanes, ZPixmap));  
}

Mat ScreenImage::XImage2MatImageAdapter(XImage *ximage)
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