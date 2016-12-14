#include "BlobTracker.h"
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>


std::string window_name = "opencv";
//int threshold_value = 0;
//int threshold_type = 1;
//int const max_value = 255;
//int const max_type = 4;
//int const max_BINARY_value = 255;

//char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
//char* trackbar_value = "Value";
cv::Mat frameMOG2;
cv::Mat thresholdOut;

/// Function headers
void Threshold_Demo(int, void*);

void BlobTracker::start(std::string file)
{
	cap.open(file);

	findBlobs();
}

cv::Mat creatMask(cv::Mat& input) {
	auto width = input.size().width;
	auto height = input.size().height;
	auto maskWidth = (width / 4);
	cv::Mat mask = cv::Mat::zeros(height, width, CV_8U);
	mask(cv::Rect(maskWidth, 0, width - maskWidth, height)) = 1;
	//std::cout << mask.size() << std::endl;
	//std::cout << input.size() << std::endl;
	return mask;
}

void BlobTracker::findBlobs()
{
	cv::Mat frame;
	cv::Mat blurOut;
	cv::Mat output;
	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2 = cv::createBackgroundSubtractorMOG2();
	std::vector<std::vector<cv::Point> > contours;
	std::vector<cv::Vec4i> hierarchy;

	std::vector<cv::Ptr<cv::Tracker>> trackers;
	std::string trackingAlg = "KCF";
	//cv::MultiTracker tracker(trackingAlg);
	std::vector<cv::Rect2d> objectsToTrack;

	cv::CascadeClassifier hAndSCascade;
	if (!hAndSCascade.load("haarcascade_upperbody.xml")) {
		std::cout << "Error |" << std::endl;
	}

	while (cvWaitKey(10) != 'q') {
		cap >> frame;
		
		if (frame.empty()) {
			break;
		}

		//std::vector<cv::Rect> hAndSs;
		//cv::resize(frame, frame, cv::Size(frame.size() / 4));
		//hAndSCascade.detectMultiScale(frame, hAndSs);

		//for (auto hAndS : hAndSs)
		//{
		//	cv::rectangle(frame, hAndS, cv::Scalar());
		//}

		cv::imshow("test", frame);

		cv::resize(frame, frame, cv::Size(frame.size() / 2));
		frame = frame + cv::Scalar(50, 50, 50);

		/*cv::Mat mask = creatMask(frame);
		cv::Mat outputMask = cv::Mat::zeros(frame.size().width, frame.size().height, CV_8U);
		frame.copyTo(outputMask, mask);*/

		pMOG2->apply(frame, frameMOG2);
		cv::threshold(frameMOG2, thresholdOut, 7, 255, 2);
		//Threshold_Demo(0, 0);
		cv::blur(thresholdOut, blurOut, cv::Size(5, 5));
		cv::dilate(blurOut, output, cv::Mat());
		cv::findContours(output, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS, CvPoint(0, 0));

		cv::Mat drawing = cv::Mat::zeros(output.size(), CV_8UC3);

		cv::RNG rng(12345);
		for (size_t i = 0; i< contours.size(); i++)
		{
			auto area = cv::contourArea(contours[i]);

			if (area < 500) {
				continue;
			}

			cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
			
			drawContours(drawing, contours, (int)i, color, 2, 8, hierarchy, 0, cv::Point());
			
			cv::Rect rect = cv::boundingRect(contours[i]);
			cv::rectangle(drawing, rect, color);
		}

		
		//tracker.update(drawing);
		std::vector<cv::Mat> images = { frame, drawing };

		int i = 0;
		for (auto image : images) {
			cv::imshow(window_name + std::to_string(i++), image);
		}
	}

	cap.release();
}

void Threshold_Demo(int, void*)
{
	/* 0: Binary
	1: Binary Inverted
	2: Threshold Truncated
	3: Threshold to Zero
	4: Threshold to Zero Inverted
	*/
	//cv::threshold(frameMOG2, thresholdOut, threshold_value, max_BINARY_value, threshold_type);
}