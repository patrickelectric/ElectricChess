/*X11 library*/
#include <X11/X.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/StringDefs.h>

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
    XImage *ximage;
    IplImage *iplImage;

    Mat XImage2MatImageAdapter();
  public:
    Mat ScreenShot();
    void ScreenInit();
    void Flush();
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
  ximage = XGetImage(display,window, 0,0 , gwa.width,gwa.height,AllPlanes, ZPixmap);  
  return XImage2MatImageAdapter();
}

Mat ScreenImage::XImage2MatImageAdapter()
{
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

void ScreenImage::Flush()
{
  XDestroyImage(ximage);
}