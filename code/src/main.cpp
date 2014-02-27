
#include "libs.h"

using namespace std;
using namespace cv;

Mat XImage2MatImageAdapter(XImage *ximage);

int main()
{
   Display *display = XOpenDisplay(NULL);
   Window root = DefaultRootWindow(display);

   XWindowAttributes gwa;

   XGetWindowAttributes(display, root, &gwa);
   int width = gwa.width;
   int height = gwa.height;


   XImage *image = XGetImage(display,root, 0,0 , width,height,AllPlanes, ZPixmap);

   Mat matImage = XImage2MatImageAdapter(image);
   
   imshow("image_show",matImage);
   waitKey(3000000);
   
   return 0;
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