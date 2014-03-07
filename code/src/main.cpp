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
#include "electricChess.h"
#include "image.h"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	Image screen_image;
	Image screen_result;
	Image chess_piece[8][8];

  ElectricChess electricChess;

	ScreenImage Screen;
	Screen.Init();

	ScreenArea ScreenArea;
	char esc;

  printf("Por favor, clice e arraste na area de analise.\n\n");
	int* cood=ScreenArea.TakeArea();

	Rect Corte(cood[0],cood[1],cood[2],cood[3]);
  	while(esc!='s')
  	{		
  		
  		//pega imagem da tela
  		screen_image.SetData(Screen.ScreenShot(),"Tela",WINDOW_NORMAL);

  		//screen_image.ScaleImg(1.0f);
  		screen_result.SetData(screen_image.img(Corte),"Result",WINDOW_NORMAL);
    	esc=screen_result.Show();
    	
      //extrai os quadrantes
      for (int i = 0; i < 8; ++i) //1-8
        for (int u = 0; u < 8; ++u) //a-h
        {
          Rect cut(screen_result.img.cols*u/8,screen_result.img.rows*i/8,screen_result.img.cols/8,screen_result.img.rows/8); //quadrados com 1/64 da area
          chess_piece[i][u].img = screen_result.img(cut); 
          char* name = electricChess.Quadrant2Char(u,i);
          chess_piece[i][u].SetData(chess_piece[i][u].img,name,WINDOW_NORMAL); //salva os dados
          printf("%s\n",electricChess.Quadrant2Char(u,i) );
          chess_piece[i][u].Show();
        }
        /*
        for (int i = 0; i < 8; ++i) //1-8
          for (int u = 0; u < 8; ++u) //a-h
            esc=chess_piece[i][u].Show();
        */

    	Screen.Flush();    	
 	}
  return 0;
}

