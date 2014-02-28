/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

/*std library*/
#include <cstdio>

#include "screenshot.h"
#include "mouseOpencv.h"

using namespace std;
using namespace cv;

int main()
{
	Mat matImage;
	char esc;
  	while(esc!='s')
  	{		
  		//matImage.setTo(Scalar(0,0,0));
  		matImage =ScreenShot();
	    imshow("image_show",matImage);
	    namedWindow("image_show", CV_WINDOW_NORMAL); 
	    esc=waitKey(10);
	    //setMouseCallback("image_show", MouseCallBackFunc, NULL);
	}
  return 0;
}