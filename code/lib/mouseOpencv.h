/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

using namespace std;
using namespace cv;

struct data_mouse {
    int event;
    int x[2];
    int y[2];   
};

class MouseOpencv 
{
  private:
    Point p;
    bool state;
    bool mouse_on;
    char* window_name;

    void MouseCallBack(int event, int x, int y, int flags, void* userdata);

  public:
    data_mouse mouseInfo;

    void Init(char* window_name_sample);
    void Capture();
};

void MouseOpencv::Init(char* window_name_sample)
{
    window_name=window_name_sample;
    state=false;
    mouse_on=false;
}

void MouseOpencv::MouseCallBack(int event, int x, int y, int flags, void* userdata)
{
    mouse_on=true;
    mouseInfo.event=event;
    switch( event )
    {
        case CV_EVENT_MOUSEMOVE:
            if(state==true)
            {
                mouseInfo.x[1]=x;
                mouseInfo.x[1]=y;
            }
        break;

        case CV_EVENT_LBUTTONDOWN:
            mouseInfo.x[0]=x;
            mouseInfo.y[0]=y;
            state=true;
        break;

        case CV_EVENT_LBUTTONUP:
            mouseInfo.x[1]=x;
            mouseInfo.y[1]=y;
            state=false;
        break;
    }
}

void MouseOpencv::Capture()
{
    //setMouseCallback(window_name, MouseCallBack, NULL);
}