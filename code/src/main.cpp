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
	ScreenImage Screen;
	Screen.ScreenInit();
	char esc;
  	while(esc!='s')
  	{		

  		matImage = Screen.ScreenShot();
  		float resizeScale=1.5f;
    	resize(matImage, matImage, Size(matImage.cols/resizeScale,matImage.rows/resizeScale));
    	
	    imshow("image_show",matImage);
	    namedWindow("image_show",CV_WINDOW_AUTOSIZE); 
	    esc=waitKey(1);
	    Screen.Flush();
	    

	    //setMouseCallback("image_show", MouseCallBackFunc, NULL);
	}
  return 0;
}