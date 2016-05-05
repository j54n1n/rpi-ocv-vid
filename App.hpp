#ifndef _APP_HPP
#define _APP_HPP

#include <iostream>
#include <sstream>
#include <cstdlib>

#include <opencv2/highgui/highgui.hpp>

template<typename CvProcessing>
class App {
  const char* winName;
  CvProcessing cvProcessing;

public:
  /**
   * Create app instance.
   * \param videoDevice the number of the video device
   * \param winName the window name
   */
  App(int videoDevice, const char* winName) {
    using namespace std;
    using namespace cv;
    this->winName = winName;
    if(!cvProcessing.initalize(videoDevice)) {
      stringstream ss;
      ss << "Cannot open video device '" << videoDevice << "'!";
      quit(ss.str().c_str(), 1);
    }
    namedWindow(this->winName, CV_WINDOW_AUTOSIZE);
  }

  /**
   * Main loop of the app.
   * \returns the last key pressed.
   */
  int run(int delayMillis = 0) {
    using namespace cv;
    if(!cvProcessing.process(this->winName)) {
      quit("Cannot process video capture!", 2);
    }
    return waitKey(delayMillis);
  }

  /**
   * Exit form app.
   */
  void quit(const char* msg = 0, int retVal = 0) {
    using namespace std;
    using namespace cv;
    destroyWindow(this->winName);
    if(retVal == 0) {
      cout << (msg == 0 ? "" : msg) << endl;
    } else {
      cerr << (msg == 0 ? "" : msg) << endl;
    }
    exit(retVal);
  }
};

#endif //_APP_HPP
