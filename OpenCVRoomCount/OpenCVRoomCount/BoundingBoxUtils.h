#pragma once
#include <opencv2/opencv.hpp>

class BoundingBoxUtils {
public:
	static const cv::Mat getImageFromBox(const cv::Mat & frame, const cv::Rect & box) {
		cv::Mat retVal(box.height, box.width, frame.type());
		for (int x = box.x; x < box.width + box.x; x++) {
			for (int y = box.y; y < box.height + box.y; y++) {
				retVal.at<cv::Vec3b>(y - box.y, x - box.x) = frame.at<cv::Vec3b>(y, x);
			}
		}

		return retVal;
	}

	static const cv::Point2f getCenterOfRect(const cv::Rect & rect) {
		return cv::Point2f((rect.x + rect.width) / 2, (rect.y + rect.height) / 2);
	}

	static const int getDistanceOfCentersBoxes(const cv::Rect & box1, const cv::Rect & box2) {
		auto center1 = getCenterOfRect(box1);
		auto center2 = getCenterOfRect(box2);

		//http://answers.opencv.org/question/14188/calc-eucliadian-distance-between-two-single-point/
		return cv::norm(center1 - center2);
	}
};
