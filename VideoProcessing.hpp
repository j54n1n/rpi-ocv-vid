#ifndef _VIDEO_PROCESSING_HPP
#define _VIDEO_PROCESSING_HPP

#include <opencv2/opencv.hpp>
#include <string>

class VideoProcessing {
  cv::VideoCapture videoCapture;
  cv::Mat frame;
  cv::Mat frameFisheyeComp;
  std::string winName;

  cv::Mat cameraMatrix;
  cv::Mat distCoeffs;

  void compensateFisheye() {
    using namespace cv;
    undistort(frame, frameFisheyeComp, cameraMatrix, distCoeffs);
    imshow(winName.c_str(), frameFisheyeComp);
  }

public:
  /**
   * Start video capturing.
   * \param videoDevice the video capture device number.
   * \returns true if the device is opened, otherwise false.
   */
  bool initalize(int videoDevice, const char* winName) {
    using namespace cv;
    using namespace std;

    cameraMatrix = (Mat_<float>(3,3) <<
        3.5923395873000760e+02f , 0.f                     , 3.1991569564808998e+02f,
        0.f                     , 3.5852312812934173e+02f , 2.4185953087165657e+02f,
        0.f                     , 0.f                     , 1.f
    );
    distCoeffs = (Mat_<float>(1,5) <<
        -3.2709008830682418e-01f ,
        9.3376576049175472e-02f  ,
        -5.1681305956487802e-03f ,
        -1.0776793003378243e-03f ,
        -1.2467313109229949e-02f
    );

    this->winName = string(winName);
    videoCapture = VideoCapture(videoDevice);
    return videoCapture.isOpened();
  }

  /**
   * Processes a video frame.
   * \param winName the window name.
   * \returns true if the operation was successful, otherwise false.
   */
  bool process() {
    using namespace cv;
    bool success = videoCapture.read(frame);
    if(success) {
      //imshow(winName.c_str(), frame);
      compensateFisheye();
    }
    return success;
  }
};

#endif //_VIDEO_PROCESSING_HPP
