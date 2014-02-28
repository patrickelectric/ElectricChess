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
  		matImage =ScreenShot();
    	resize(matImage, matImage, Size(matImage.cols/2,matImage.rows/2));
	    imshow("image_show",matImage);
	    namedWindow("image_show",CV_WINDOW_AUTOSIZE); 
	    esc=waitKey(1);
	    //setMouseCallback("image_show", MouseCallBackFunc, NULL);
	}
  return 0;
}