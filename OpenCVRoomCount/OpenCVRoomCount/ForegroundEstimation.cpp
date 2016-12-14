#include "ForegroundEstimation.h"

void ForegroundEstimation::countPixels() {
	if (whitePixelCount.size() == 0) {
		std::cout << ("Intialising") << std::endl;
		std::vector<std::vector<int>> init(edgedFrame.rows, std::vector<int>(edgedFrame.cols));
		whitePixelCount = init;
	}

	for (int i = 0; i < edgedFrame.rows; i++) {
		for (int j = 0; j < edgedFrame.cols; j++) {
			if (edgedFrame.at<uchar>(i, j) == 255) {
				whitePixelCount[i][j] += 1;
			}
		}
	}
}

int largestNumber(std::vector<std::vector<int>> vector) {
	int largestNumber = 0;
	for (uint i = 0; i < vector.size(); i++) {
		for (uint j = 0; j < vector[i].size(); j++) {
			largestNumber = vector[i][j] > largestNumber ? vector[i][j] : largestNumber;
		}
	}

	return largestNumber;
}

cv::Mat ForegroundEstimation::reduceToWhitePixels() {
	//std::cout << "frame:" << frameNumber <<" largestNumber: " << largestNumber(whitePixelCount) << std::endl;
	cv::Mat foreground = cv::Mat::zeros(whitePixelCount.size(), whitePixelCount[0].size(), CV_8U);
	for (uint i = 0; i < whitePixelCount.size(); i++) {
		for (uint j = 0; j < whitePixelCount[0].size(); j++) {
			double probabilityOfBackground = (double) whitePixelCount[i][j] / (double) frameNumber;
			if (probabilityOfBackground <= threshold && edgedFrame.at<uchar>(i, j) == 255) {
				foreground.at<uchar>(i, j) = 255;
			}
		}
	}

	return foreground;
}

cv::Mat ForegroundEstimation::getForeground(cv::Mat edgedFrame_, int frameNumber_) {
	edgedFrame = edgedFrame_;
	frameNumber = frameNumber_;
	countPixels();
	return reduceToWhitePixels();

}