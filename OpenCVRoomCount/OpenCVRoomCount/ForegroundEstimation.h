#pragma once

#include <stdio.h>
#include <opencv2/opencv.hpp>

class ForegroundEstimation {
	//Every pixel in frame, we count the number of times it's white across time.
public :
	cv::Mat getForeground(cv::Mat edgedFrame, int frameNumber);
private:
	std::vector<std::vector<int>> whitePixelCount;
	void countPixels();
	double threshold = 0.65;
	int frameNumber;
	cv::Mat edgedFrame;
	cv::Mat reduceToWhitePixels();

};
