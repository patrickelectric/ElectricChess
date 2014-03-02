/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

/*std library*/
#include <cstdio>

#include "screenshot.h"
#include "screenArea.h"
#include "image.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Image screen_image;

	ScreenImage Screen;
	Screen.Init();

	ScreenArea ScreenArea;
	char esc;


	int* cood=ScreenArea.TakeArea();

	Rect Corte(cood[0],cood[1],cood[2],cood[3]);
  	while(esc!='s')
  	{		
  		
  		//pega imagem da tela
  		screen_image.SetData(Screen.ScreenShot(),"Tela",WINDOW_NORMAL);

  		//screen_image.ScaleImg(1.0f);
  		Mat result=screen_image.img(Corte);
    	imshow("Result",result);
    	namedWindow("Result",WINDOW_NORMAL); 
    	esc=screen_image.Show();


    	//O buffer do screen_image precisa ser limpo após tratamento com a imagem
    	Screen.Flush();    	
 	}
  return 0;
}

