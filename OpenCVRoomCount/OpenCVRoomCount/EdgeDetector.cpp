#include "EdgeDetector.h"

EdgeDetector::EdgeDetector(cv::Mat& orginal_) : 
	originalFrame(orginal_)
{

}

cv::Mat EdgeDetector::getEdgeFrame() {
	cv::Mat threshImg, blurredImage,greyScale;
	cv::cvtColor(originalFrame, greyScale, CV_BGR2GRAY);
	cv::blur(greyScale, blurredImage, cv::Size(7, 7));
	double otsuThreshVal = cv::threshold(blurredImage, threshImg, 125, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
	cv::Canny(blurredImage, edgeFrame, otsuThreshVal, otsuThreshVal*0.5);
	return edgeFrame;
}