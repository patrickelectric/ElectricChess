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
#include "image.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Image screen_image;
	Image screen_result;

	ScreenImage Screen;
	Screen.ScreenInit();

	/// Do the Matching and Normalize
    int match_method=1; //1-5

	char esc;
  	while(esc!='s')
  	{		

  		//pega imagem da tela
  		screen_image.SetData(Screen.ScreenShot(),"Tela",WINDOW_NORMAL);
  		screen_image.ScaleImg(1.5f);
    	//O buffer do screen_image precisa ser limpo após tratamento com a imagem
    	Screen.Flush();
    
	    Mat analize = imread(argv[1], CV_LOAD_IMAGE_COLOR);

	    cvtColor(analize, analize, CV_RGB2GRAY);
	    cvtColor(screen_image.img, screen_image.img, CV_RGB2GRAY);

	    screen_result=screen_image;
	    matchTemplate( screen_image.img, analize, screen_result.img, match_method );
        normalize( screen_result.img, screen_result.img, 0, 1, NORM_MINMAX, -1, Mat() );

        /// Localizing the best match with minMaxLoc
        double minVal; double maxVal; Point minLoc; Point maxLoc;
        Point matchLoc;
        minMaxLoc( screen_result.img, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );

		/// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
		if( match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED )
		    { matchLoc = minLoc; }
		else
		    { matchLoc = maxLoc; }

		cvtColor(screen_result.img, screen_result.img, CV_GRAY2RGB);

		line(screen_image.img, Point (0,matchLoc.y), Point (screen_image.img.cols,matchLoc.y), cvScalar(205,201,201), 1, 8, 0);
        line(screen_image.img, Point (matchLoc.x,0), Point (matchLoc.x,screen_image.img.rows), cvScalar(205,201,201), 1, 8, 0);

        screen_result.SetData(screen_result.img,"Resultado",WINDOW_NORMAL);
        esc=screen_image.Show(); 
        //esc=screen_result.Show();
        //printf("%f < result\n",(float)screen_result.img.cols/screen_result.img.rows );
        //printf("%f < screen\n",(float)screen_image.img.cols/screen_image.img.rows );

	    //setMouseCallback("image_show", MouseCallBackFunc, NULL);
	}
  return 0;
}