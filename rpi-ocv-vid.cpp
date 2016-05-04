#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(int argc, char* argv[])
{
    VideoCapture cap(0); // open /dev/video0 (bcm2835-v4l2) for reading

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

    //double fps = cap.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video
    //This request is not working with the bcm2835-v4l2 driver.
    //cout << "Frame per seconds : " << fps << endl;

    namedWindow("RPiVideo",CV_WINDOW_AUTOSIZE); //create a window called "RPiVideo"

    while(1)
    {
        Mat frame;

        bool bSuccess = cap.read(frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
                        cout << "Cannot read the frame from video file" << endl;
                       break;
        }

        imshow("RPiVideo", frame); //show the frame in the window

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl;
                break;
       }
    }

    return 0;

}
