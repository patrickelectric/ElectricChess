/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

/*std library*/
#include <cstdio>

#include "screenshot.h"

using namespace std;
using namespace cv;

Mat XImage2MatImageAdapter(XImage *ximage);

int main()
{
  Mat matImage = ScreenShot();
  imshow("image_show",matImage);
  waitKey(3000000);
   
  return 0;
}