// OpenCVRoomCount.cpp : Defines the entry point for the console application.
//

#include <opencv2/opencv.hpp>
#include "PeopleCounter.h"
using namespace cv;
int main(int argc, char* argv[])
{
	PeopleCounter pc = PeopleCounter();
	pc.start();
	//HOGAlogrithm(cap);
	//BlobTracker bt = BlobTracker();
	//bt.start("video\\FYP-PeopleTracking.mp4");
	//VideoCapture vc = VideoCapture("video\\FYP-PeopleTracking.mp4");
	//cv::Mat frame;
	//ForegroundEstimation foreground = ForegroundEstimation();
	//cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2 = cv::createBackgroundSubtractorMOG2(100);
	//while (cvWaitKey(25) != 'q') {
	//	vc >> frame;
	//	int frameNumber = vc.get(CV_CAP_PROP_POS_FRAMES);
	//	if (frame.empty()) {
	//		break;
	//	}
	//	
	//	//cv::resize(frame, frame, cv::Size(frame.size() / 3));
	//		
	//	EdgeDetector edge = EdgeDetector(frame);
	//	cv::Mat frameMOG;
	//	pMOG2->apply(edge.getEdgeFrame(), frameMOG);
	//	//cv::Mat foregroundFrame = foreground.getForeground(edge.getEdgeFrame(), frameNumber);
	//	
	//	ContourFinder contourFinder = ContourFinder(frameMOG, 100);
	//	contourFinder.findContours();

	//	/*cv::RNG rng(12345);
	//	cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
	//	cv::Mat drawing = cv::Mat::zeros(frame.size(), CV_8UC3);
	//	contourFinder.drawContours(drawing);
	//	auto boundingBoxes = contourFinder.getBoundingBoxesOfCountours();
	//	for (auto box : boundingBoxes) {
	//		cv::rectangle(frame, box, color);
	//	}*/
	//	
	//	cv::imshow("edged", edge.getEdgeFrame());
	//	/*cv::imshow("test", foregroundFrame);*/
	//	cv::imshow("frame", frame);
	//	//cv::imshow("drawing", drawing);
	//	
	//	cv::imshow("mog", frameMOG);
	//}

	return 0;

}

//#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/highgui/highgui.hpp"
//#include <stdlib.h>
//#include <stdio.h>
//
//using namespace cv;
//
///// Global variables
//
//int threshold_value = 0;
//int threshold_type = 3;;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;
//
//Mat src, src_gray, dst;
//char* window_name = "Threshold Demo";
//
//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
//
///// Function headers
//void Threshold_Demo(int, void*);
//
///**
//* @function main
//*/
//int main(int argc, char** argv)
//{
//	/// Load an image
//	VideoCapture vc= VideoCapture("video\\TownCentreXVID.avi");
//	vc >> src;
//
//	/// Convert the image to Gray
//	cvtColor(src, src_gray, CV_BGR2GRAY);
//
//	/// Create a window to display results
//	namedWindow(window_name, CV_WINDOW_AUTOSIZE);
//
//	/// Create Trackbar to choose type of Threshold
//	createTrackbar(trackbar_type,
//		window_name, &threshold_type,
//		max_type, Threshold_Demo);
//
//	createTrackbar(trackbar_value,
//		window_name, &threshold_value,
//		max_value, Threshold_Demo);
//
//	/// Call the function to initialize
//	Threshold_Demo(0, 0);
//
//	/// Wait until user finishes program
//	while (true)
//	{
//		int c;
//		c = waitKey(20);
//		if ((char)c == 27)
//		{
//			break;
//		}
//	}
//
//}
//
//
///**
//* @function Threshold_Demo
//*/
//void Threshold_Demo(int, void*)
//{
//	/* 0: Binary
//	1: Binary Inverted
//	2: Threshold Truncated
//	3: Threshold to Zero
//	4: Threshold to Zero Inverted
//	*/
//
//	threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
//
//	imshow(window_name, dst);
//}