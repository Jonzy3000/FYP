#pragma once
#include <opencv2/opencv.hpp>

class BackgroundSubtractionProcessor {
public: 
	BackgroundSubtractionProcessor() 
	{
		pMOG2 = cv::createBackgroundSubtractorMOG2();
	}

	cv::Mat process(cv::Mat & frame) {
		cv::Mat frameMOG2;
		pMOG2->apply(frame, frameMOG2);

	}
	


private:
	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2;

};