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
    XImage *ximage;
    IplImage *iplImage;

    //Mat XImage2MatImageAdapter();
    void XImage2Mat(const XImage *src, cv::Mat& result);
  public:
    void ScreenShot(Mat& result);
    void Init();
    void Flush();
};

void ScreenImage::Init()
{
  display = XOpenDisplay(NULL);
}

void ScreenImage::ScreenShot(Mat& result)
{
  XWindowAttributes gwa;
  XGetWindowAttributes(display, DefaultRootWindow(display), &gwa);
  ximage = XGetImage(display,DefaultRootWindow(display), 0,0 , gwa.width,gwa.height,AllPlanes, ZPixmap);  
  XImage2Mat(ximage, result);
}

/*
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
  cvReleaseImage(&iplImage);
  return imgmat;
};
*/

void ScreenImage::XImage2Mat(const XImage *src, cv::Mat& result)
{
  int x, y;
  char *cp;
  uint32_t pixel;

  result.create(cv::Size(src->width, src->height), CV_8UC3);

  for (y = 0;y < src->height;y++) {
    cp = src->data + y * src->bytes_per_line;
    for (x = 0;x < src->width;x++) {
      pixel = *(uint32_t *)cp;

      result.data[(y*result.cols + x)*3] = (pixel & 0x000000ff) >> 0;
      result.data[(y*result.cols + x)*3 + 1] = (pixel & 0x0000ff00) >> 8;
      result.data[(y*result.cols + x)*3 + 2] = (pixel & 0x00ff0000) >> 16;
      cp += 4;
    }
  }
}

void ScreenImage::Flush()
{
  XFlush(display);
  //_mm_free(ximage->data);
  XDestroyImage(ximage);
}