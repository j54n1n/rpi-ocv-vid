#include <iostream>

#include <opencv2/opencv.hpp>

#include "App.hpp"
#include "VideoProcessing.hpp"

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
  const char* WIN_NAME = "RPiOCVvid";
  App<VideoProcessing> app(0, WIN_NAME);
  int key = 0;
  int fps = 10;

  cout << "Using OpenCV version " << CV_VERSION << "." << endl;
  cout << "Press 'q' to quit." << endl << endl;

  while(key != 'q') {
    key = app.run(1000/fps);
    if(!cvGetWindowHandle(WIN_NAME)) {
      // The handle will be a nullptr when the window gets closed.
      break;
    }
  }

  app.quit();
}
