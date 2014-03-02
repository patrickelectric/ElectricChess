#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

class Image 
{
  //private:

  public:
    Mat img;
    char* window_name;
    int window_flag; //WINDOW_NORMAL - WINDOW_AUTOSIZE - WINDOW_OPENGL

    void SetData(Mat img_sample,char* window_name_sample ,int window_flag_sample);
    void ScaleImg(float scale);
    char Show();
};

void Image::SetData(Mat img_sample,char* window_name_sample ,int window_flag_sample)
{
    img=img_sample;
    window_name=window_name_sample;
    window_flag=window_flag_sample;
}

char Image::Show()
{
    imshow(window_name,img);
    namedWindow(window_name,window_flag); 
    return waitKey(1);
}

void Image::ScaleImg(float scale)
{
    resize(img, img, Size(img.cols*scale,img.rows*scale));
}