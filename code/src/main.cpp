/*X11 library*/
#include <X11/Xlib.h>
#include <X11/X.h>

/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

/*std library*/
#include <cstdio>
#include <unistd.h>

#include "screenshot.h"
#include "screenArea.h"
#include "electricChess.h"
#include "image.h"

using namespace std;
using namespace cv;

float diffMat(Mat im1, Mat im2);

int main(int argc, char** argv)
{
	Image screen_image;
	Image screen_result;
  Image first_img;
	Image chess_piece[8][8];

  ElectricChess electricChess;

	ScreenImage Screen;
	Screen.Init();

	ScreenArea ScreenArea;
	char esc;

  printf("Por favor, clice e arraste na area de analise.\n\n");
	int* cood=ScreenArea.TakeArea();

	Rect Corte(cood[0],cood[1],cood[2],cood[3]);

  bool  first_time=false;  
	while(esc!='s')
	{		
		
		/// pega imagem da tela
    Screen.ScreenShot(screen_image.img);
		screen_image.SetData(screen_image.img.clone(),"Tela",WINDOW_AUTOSIZE);

		/// corta a imagem para a area selecionada
		screen_result.SetData(screen_image.img(Corte),"Result",WINDOW_AUTOSIZE);
    if(first_time==false)
    {
      first_img.img=screen_result.img.clone();
      first_img.SetData(first_img.img,"1",WINDOW_AUTOSIZE);
      first_time=true;
    }

    esc=screen_result.Show();
    esc=first_img.Show();

    /// extrai os quadrantes
    for (int i = 0; i < 8; ++i) //1-8
      for (int u = 0; u < 8; ++u) //a-h
      {
        Rect cut(screen_result.img.cols*u/8,screen_result.img.rows*i/8,screen_result.img.cols/8,screen_result.img.rows/8); //quadrados com 1/64 da area
        chess_piece[i][u].img = screen_result.img(cut); 
        char* name = electricChess.Quadrant2Char(u,i);
        chess_piece[i][u].SetData(chess_piece[i][u].img,name,WINDOW_AUTOSIZE); //salva os dados
        #if 0
        if(i<2 || i>5)
          chess_piece[i][u].Show();
        #endif
      }
    /// printa os dados do mouse
    printf("screen_result x-y %d-%d  ; event %d ; flag %d\n",screen_result.mouse.x,screen_result.mouse.y,screen_result.mouse.event,screen_result.mouse.flag);
    printf("first_img     x-y %d-%d  ; event %d ; flag %d\n",first_img.mouse.x,first_img.mouse.y,first_img.mouse.event,first_img.mouse.flag);

    Screen.Flush();  

 	}
  return 0;
}


/// http://rosettacode.org/wiki/Percentage_difference_between_images
float diffMat(Mat im1, Mat im2)
{
  float totalDiff=0.0f;
  if ( (im1.cols != im2.cols) || (im1.rows !=im2.rows) )
  {
    printf("width/height of the images must match!\n");
  } 
  else 
  {
    /* BODY: the "real" part! */
    for(int x=0; x < im1.rows; x++)
    {
      for(int y=0; y < im1.cols; y++)
      {
        //printf("%f\n",totalDiff );
        //totalDiff += (float)((float)im1.at<uchar>(x,y) - (float)im2.at<uchar>(x,y))/255.0;
      }
    }
  } 
  return 100.0*totalDiff/(double)(im1.cols * im1.rows);
}