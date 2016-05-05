#include <opencv2/core/version.hpp>
#include <opencv2/highgui/highgui_c.h>
#include <iostream>

#include "App.hpp"
#include "VideoProcessing.hpp"

using namespace cv;
using namespace std;

int main(int argc, char* argv[]) {
  const char* WIN_NAME = "RPiOCVvid";
  App<VideoProcessing> app(0, WIN_NAME);
  int key = 0;

  cout << "Using OpenCV version " << CV_VERSION << "." << endl;
  cout << "Press 'q' to quit." << endl << endl;

  while(key != 'q') {
    key = app.run(40);
    if(!cvGetWindowHandle(WIN_NAME)) {
      break;
    }
  }

  app.quit();
}
