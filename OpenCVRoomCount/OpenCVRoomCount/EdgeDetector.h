#pragma once

#include <stdio.h>
#include <opencv2/opencv.hpp>

class EdgeDetector {
public:
	EdgeDetector(cv::Mat& originalFrame);
	cv::Mat getEdgeFrame();

private:
	cv::Mat originalFrame;
	cv::Mat edgeFrame;
};