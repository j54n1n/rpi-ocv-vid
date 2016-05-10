#ifndef _VIDEO_PROCESSING_HPP
#define _VIDEO_PROCESSING_HPP

#include <opencv2/opencv.hpp>

class VideoProcessing {
  cv::VideoCapture videoCapture;

  void compensateFisheye(const char* nm, cv::Mat& frame) {
    using namespace cv;
    Mat cameraMatrix = Mat::zeros(3, 3, CV_32FC1);
    //Mat cameraMatrix = (Mat_<double>(3,3) << 1000, 0, 320, 0, 1000, 240, 0, 0, 1);
    CvMat cvCameraMatrix = cameraMatrix;
    cvSetReal2D(&cvCameraMatrix, 0, 0, 469.96);
    cvSetReal2D(&cvCameraMatrix, 0, 1, 0.0);
    cvSetReal2D(&cvCameraMatrix, 0, 2, 640.0);
    cvSetReal2D(&cvCameraMatrix, 1, 0, 0.0);
    cvSetReal2D(&cvCameraMatrix, 1, 1, 467.68);
    cvSetReal2D(&cvCameraMatrix, 1, 2, 360);
    cvSetReal2D(&cvCameraMatrix, 2, 0, 0.0);
    cvSetReal2D(&cvCameraMatrix, 2, 1, 0.0);
    cvSetReal2D(&cvCameraMatrix, 2, 2, 1.0);
    Mat distCoeffs = Mat::zeros(1, 5, CV_32FC1);
    //Mat distCoeffs = (Mat_<double>(5,1) << 0.1, 0.01, -0.001, 0, 0);
    CvMat cvDistCoeffs = distCoeffs;
    cvSetReal2D(&cvDistCoeffs, 0, 0, -0.18957);
    cvSetReal2D(&cvDistCoeffs, 0, 1, 0.037319);
    cvSetReal2D(&cvDistCoeffs, 0, 2, 0.0);
    cvSetReal2D(&cvDistCoeffs, 0, 3, 0.0);
    cvSetReal2D(&cvDistCoeffs, 0, 4, -0.00337);
    Mat undistortedCameraMatrix = getOptimalNewCameraMatrix(
        cameraMatrix, distCoeffs, frame.size(), 1
    );
    Mat newFrame;
    undistort(frame, newFrame, cameraMatrix, distCoeffs);
    imshow(nm, newFrame);
  }

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
      //compensateFisheye(winName, frame);
    }
    return success;
  }
};

#endif //_VIDEO_PROCESSING_HPP
