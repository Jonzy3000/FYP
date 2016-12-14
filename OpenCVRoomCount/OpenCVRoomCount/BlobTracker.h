#pragma once

#include <stdio.h>
#include <opencv2/opencv.hpp>


class BlobTracker {
public:
	void start(std::string file);

private:
	void update();
	void findBlobs();
	int count;
	cv::VideoCapture cap;
};
