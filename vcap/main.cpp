#include <stdio.h>
#include <iostream>
#include <opencv2/opencv.hpp>
//#include <string>
using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
    VideoCapture cap(0);//Default camera
    //VideoCapture cap("/home/debian/vcap/sensor.mp4");//open video file

    if (!cap.isOpened()) {
        printf("Video is not opened. \n");
        return -1;
    }
    else {
        printf("Video is opened. \n");
    }

    union { int v; char c[5]; } uEx;
    uEx.v = static_cast<int>(cap.get(CV_CAP_PROP_FOURCC));
    uEx.c[4] = '\0';
    printf("Codec: %s \n",uEx.c);

    Size S = Size((int)cap.get(CV_CAP_PROP_FRAME_WIDTH),(int)cap.get(CV_CAP_PROP_FRAME_HEIGHT));
    printf("Frame size: %d x %d \n",S.width,S.height);

    double rate = cap.get(CV_CAP_PROP_FPS);//Frame rate
    printf("Frame rate: %f \n", rate);
    int dperiod = 1000 / rate;

    int ex = CV_FOURCC('M', 'J', 'P', 'G');
    //int ex = CV_FOURCC('X', 'V', 'I', 'D');//https://www.xvid.com/
    //int ex = -1;//pop up window to choose
    rate = 30;
    const string vpath="/home/debian/vcap/vdowr.avi";
    VideoWriter outputVideo(vpath, ex , rate, S, true);
    if (!outputVideo.isOpened())
    {
        cout << "Could not open the output video to write."<< endl;
        waitKey(5000);
        return -1;
    }


    Mat frame;
    for (int i = 0;; i++) {
        if (!cap.read(frame)) break;
        outputVideo << frame;
        imshow("Frame", frame);
        if (waitKey(dperiod) == 27) break; //if 'Esc' key is pressed
    }
    cap.release();
    outputVideo.release();
    //waitKey(5000);
    return 0;
}
