#pragma once
#include <opencv2/opencv.hpp>

class BoundingBoxUtils {
public:
	static const cv::Mat getImageFromBox(const cv::Mat & frame, const cv::Rect & box) {
		cv::Mat retVal (box.height, box.width, frame.type());
		for (int x = box.x; x < box.width + box.x; x++) {
			for (int y = box.y; y < box.height + box.y; y++) {
				retVal.at<cv::Vec3b>(y - box.y, x - box.x) = frame.at<cv::Vec3b>(y, x);
			}
		}

		return retVal;
	}
};
