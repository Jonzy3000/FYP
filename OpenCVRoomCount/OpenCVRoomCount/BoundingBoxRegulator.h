#pragma once
#include <opencv2/opencv.hpp>

class BoundingBoxRegulator {
public:
	BoundingBoxRegulator(double maxArea_, double maxWidth_, double maxHeight_) : 
		maxArea(maxArea_),
		maxWidth(maxWidth_),
		maxHeight(maxHeight_)
	{}

	std::vector<cv::Rect> regulateBoxes(std::vector<cv::Rect> boxesToRegulate) {
		std::vector<cv::Rect> updatedBoxes;
		for (auto box : boxesToRegulate) {
			if (box.area > maxArea) {
				if (box.width > maxWidth) {
					int splitIntoNParts = floor(box.width / maxWidth);
					if (splitIntoNParts > 1) {
						double newWidth = box.width / (double)splitIntoNParts;
						double xOfBox = box.x;
						for (int i = 0; i < splitIntoNParts; i++) {
							cv::Rect reducedBox = cv::Rect(xOfBox, box.y, newWidth, box.height);
							xOfBox += newWidth;
							updatedBoxes.push_back(reducedBox);
						}
					}
				}
				else if (box.height > maxHeight) {
					int splitIntoNParts = floor(box.height / maxHeight);
					if (splitIntoNParts > 1) {
						double newHeight = box.height / (double)splitIntoNParts;
						double yOfBox = box.y;

						for (int i = 0; i < splitIntoNParts; i++) {
							cv::Rect reducedBox = cv::Rect(box.x, yOfBox, box.width, newHeight);
							yOfBox += newHeight;
							updatedBoxes.push_back(reducedBox);
						}
					}

				}
			}
			else {
				updatedBoxes.push_back(box);
			}
		}
	}
private:
	double maxArea;
	double maxWidth;
	double maxHeight;
};