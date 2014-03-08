#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

class Image 
{
  private:
    static void mouseCallback(int event, int x, int y, int flags, void *param);
    void doMouseCallback(int event, int x, int y, int flags);

  public:
    struct Mouse{int x; int y; int event; int flag;};
    Mouse mouse;

    Mat img;
    char* window_name;
    int window_flag; //WINDOW_NORMAL - WINDOW_AUTOSIZE - WINDOW_OPENGL

    void SetData(Mat img_sample,char* window_name_sample ,int window_flag_sample);
    void ScaleImg(float scale);
    char Show();
};

Image* ins;

void Image::SetData(Mat img_sample,char* window_name_sample ,int window_flag_sample)
{
    ins=this;
    img=img_sample;
    window_name=window_name_sample;
    window_flag=window_flag_sample;
}

void Image::ScaleImg(float scale)
{
    resize(img, img, Size(img.cols*scale,img.rows*scale));
}

char Image::Show()
{
    namedWindow(window_name,window_flag); 
    imshow(window_name,img);
    setMouseCallback(window_name, mouseCallback, NULL);
    return waitKey(1);
}

void Image::mouseCallback(int event, int x, int y, int flags, void *param)
{
    ins->doMouseCallback( event, x, y, flags);
}

void Image::doMouseCallback(int event, int x, int y, int flags)
{
    mouse.x=x;
    mouse.y=y;
    mouse.event=event;
    mouse.flag=flags;
}