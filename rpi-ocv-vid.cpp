#include <iostream>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <stdint.h>
#include <unistd.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

int main(int argc, char* argv[]) {
	const char* windowNameSource       = "CameraSource";
	const char* windowNameCompensation = "CameraCompensation";
	const char* windowNameMotion       = "CameraMotion";
	const int targetFps = 25;
	const int waitMs = 1000 / targetFps;
	const int motionTreshold = 64;
	
	//These coeeficients are size dependent!
	const Mat cameraMatrix = (Mat_<float>(3,3) <<
		3.5923395873000760e+02f , 0.f                     , 3.1991569564808998e+02f,
		0.f                     , 3.5852312812934173e+02f , 2.4185953087165657e+02f,
		0.f                     , 0.f                     , 1.f
	);
        const Mat distCoeffs = (Mat_<float>(1,5) <<
		-3.2709008830682418e-01f ,
		 9.3376576049175472e-02f ,
 		-5.1681305956487802e-03f ,
		-1.0776793003378243e-03f ,
		-1.2467313109229949e-02f
	);
	Mat remap1;
	Mat remap2;
	
	float fps = 0;
	float sec = 0;
	int counter = 0;
	int fpsDiff = 0;
	time_t timeStart;
	time_t timeStop;
	
	Point pointMin;
	Point pointMax;
	
	Mat frame;
	Mat imageUndistorted;
	Mat imageGrayscale;
	Mat imageGrayscaleProcessing;
	Mat imageMotionMask;
	
	VideoCapture videoCapture(0);
	//RPi V4L2 driver does not allow size changes.
	//videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 320);
	//videoCapture.set(CV_CAP_PROP_FRAME_WIDTH, 240);
	if(!videoCapture.isOpened()) {
		return -1;
	}
	
	// Extract first image.
	videoCapture >> frame;
	
	imshow(windowNameSource, frame);
	
	//Init fisheye compensation.
	initUndistortRectifyMap(cameraMatrix, distCoeffs,
							Mat(), cameraMatrix, frame.size(),
							CV_32FC2, remap1, remap2);
	remap(frame, imageUndistorted, remap1, remap2, INTER_LINEAR);
	
	
	//Reduce size & depth for motion detection.
	cvtColor(imageUndistorted, imageGrayscale, CV_BGR2GRAY);
	blur(imageGrayscale, imageGrayscale, Size(3, 3));
	
	imageMotionMask = Mat(frame.size(), CV_8U);
		
	waitKey(waitMs);
	
	cout << "Using OpenCV version " << CV_VERSION << "." << endl;
	cout << "Press 'q' to quit." << endl << endl;
	
	//Start timer
	time(&timeStart);
	
	while(true) {
		videoCapture >> frame;
		if(frame.empty()) {
			break;
		}
		
		imshow(windowNameSource, frame);
		
		//Compensate fisheye effect.
		remap(frame, imageUndistorted, remap1, remap2, INTER_LINEAR);
		
		imshow(windowNameCompensation, imageUndistorted);
		
		//Reduce depth for motion detection.
		cvtColor(imageUndistorted, imageGrayscaleProcessing, CV_BGR2GRAY);
		blur(imageGrayscaleProcessing, imageGrayscaleProcessing,
		     Size(3, 3));
		
		const int frameWidth = min(imageGrayscale.size().width,
				imageGrayscaleProcessing.size().width);
		const int frameHeight = min(imageGrayscale.size().height,
				imageGrayscaleProcessing.size().height);
		
		pointMin = Point(frameWidth, frameHeight);
		pointMax = Point(0, 0);
		
		//Find area with motion.
		for(int i = 0; i < frameWidth; i++) {
			for(int j = 0; j < frameHeight; j++) {
				if(abs(imageGrayscale.at<uint8_t>(Point(i, j)) -
					   imageGrayscaleProcessing.at<uint8_t>(Point(i, j)))
					   > motionTreshold) {
					//Motion detected.
					imageMotionMask.at<uint8_t>(Point(i, j)) = 255;
					if(i < pointMin.x) {
						pointMin.x = i;
					}
					if(j < pointMin.y) {
						pointMin.y = j;
					}
					if(i > pointMax.x) {
						pointMax.x = i;
					}
					if(j > pointMax.y) {
						pointMax.y = j;
					}
				} else {
					//No Motion.
					imageMotionMask.at<uint8_t>(Point(i, j)) = 0;
				}
			}
		}
		imageGrayscale = imageGrayscaleProcessing.clone();
		
		//Show motion window.
		rectangle(imageMotionMask, pointMin, pointMax, Scalar(128));
		imshow(windowNameMotion, imageMotionMask);
		
		//Calculate fps.
		++counter;
		if((counter % 100) == 0) {
			time(&timeStop);
			sec = (float)difftime(timeStop, timeStart);
			fps = counter / sec;
			cout << fps << "fps" << endl;
		}
		
		//Ceck quit key press.
		int key = waitKey(waitMs);
		if(key == 'q') {
			break;
		}
		//Close app if any of the windows closes.
		if(!cvGetWindowHandle(windowNameSource)) {
			break;
		}
		if(!cvGetWindowHandle(windowNameCompensation)) {
			break;
		}
		if(!cvGetWindowHandle(windowNameMotion)) {
			break;
		}
	}
	
	destroyAllWindows();
}
