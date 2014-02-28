/*OpenCV library*/
#include <opencv/cv.h>
#include <opencv/highgui.h>

struct data_mouse {
    int event;
    int x[2];
    int y[2];   
};

class MouseOpencv 
{
  private:
    bool state;
    bool mouse_on;

  public:
    data_mouse mouseInfo;

    void MouseCallBackFunc(int event, int x, int y, int flags, void* userdata);
    void MouseOpencvInit();
};

void MouseOpencv::MouseOpencvInit()
{
    state=false;
    mouse_on=false;
}

void MouseOpencv::MouseCallBackFunc(int event, int x, int y, int flags, void* userdata)
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