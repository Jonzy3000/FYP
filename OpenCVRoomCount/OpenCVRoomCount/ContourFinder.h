#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include "BoundingBox.h"
/*
bool doesBoxIntersectOnTheXYAxis(BoundingBox box) {
return fabs(x - box.x) * 2 < width + box.width &&
fabs(y - box.y) * 2 < width + box.width;
}*/
class ContourFinder {
public:
	ContourFinder(cv::Mat source, int minSize) : 
		source(source), 
		minSize(minSize) 
	{

	}

	std::vector<std::vector<cv::Point>> findContours() {
		std::vector<cv::Vec4i> hierarchy;

		cv::findContours(source, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

		removeCountoursThatAreTooSmall();

		return contours;
	}

	std::vector<cv::Rect> getBoundingBoxesOfCountours() {
		std::vector<cv::Rect> boundingBoxes;
		for (auto contour : contours) {
			boundingBoxes.push_back(cv::boundingRect(contour));
		}

		return boundingBoxes;
	}

	std::vector<std::vector<cv::Point> > getConvexHulls() {
		if (contours.size() == 0) {
			throw std::exception("No contours found, try calling findContours");
		}

		std::vector<std::vector<cv::Point> > convexHulls(contours.size());

		for (size_t i = 0; i < contours.size(); i++) {
			auto contour = cv::Mat(contours[i]);
			cv::convexHull(contour, convexHulls[i]);
		}

		return convexHulls;
	}

	void drawBoundingRects(std::vector<cv::Rect> boundingBoxes, cv::Mat & frame) {
		cv::Scalar colour = cv::Scalar(10, 255, 10);
		for (auto box : boundingBoxes) {
			cv::rectangle(frame, box, colour);
		}
	}

	void drawContours(cv::Mat & frame) {
		cv::RNG rng(12345);
		cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
		for (size_t i = 0; i < contours.size(); i++) {
			cv::drawContours(frame, contours, i, color);
		}
	}

	void drawConvexHulls(cv::Mat & frame, std::vector<std::vector<cv::Point> > convexHulls) {
		for (size_t i = 0; i < contours.size(); i++) {
			if (i >= convexHulls.size()) {
				break;
			}

			cv::drawContours(frame, convexHulls, i, cv::Scalar(22, 22, 200));
		}
	}

private:
	cv::Mat source;
	int minSize;
	std::vector<std::vector<cv::Point> > contours;

	void removeCountoursThatAreTooSmall() {
		for (int i = contours.size() - 1; i >= 0; i--) {
			auto area = cv::contourArea(contours[i]);

			if (area < minSize) {
				contours.erase(contours.begin() + i);
			}
		}
	}
};