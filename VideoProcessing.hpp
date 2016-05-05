#ifndef _VIDEO_PROCESSING_HPP
#define _VIDEO_PROCESSING_HPP

#include <opencv2/highgui/highgui.hpp>

class VideoProcessing {
  cv::VideoCapture videoCapture;

public:
  /**
   * Start video capturing.
   * \param videoDevice the video capture device number.
   * \returns true if the device is opened, otherwise false.
   */
  bool initalize(int videoDevice) {
    using namespace cv;
    videoCapture = VideoCapture(videoDevice);
    return videoCapture.isOpened();
  }

  /**
   * Processes a video frame.
   * \param winName the window name.
   * \returns true if the operation was successful, otherwise false.
   */
  bool process(const char* winName) {
    using namespace cv;
    Mat frame;
    bool success = videoCapture.read(frame);
    if(success) {
      imshow(winName, frame);
    }
    return success;
  }
};

#endif //_VIDEO_PROCESSING_HPP
