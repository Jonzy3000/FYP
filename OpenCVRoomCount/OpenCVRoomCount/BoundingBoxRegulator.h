#pragma once
#include <opencv2/opencv.hpp>
#include "ConfigOptions.h"

typedef std::pair < cv::Rect, std::vector<cv::Point>> RectAndConvexHull;

class BoundingBoxRegulator {
public:
	BoundingBoxRegulator(int maxArea_, int maxWidth_, int maxHeight_) :
		maxArea(maxArea_),
		maxWidth(maxWidth_),
		maxHeight(maxHeight_)
	{}

	BoundingBoxRegulator(const ConfigOptions::PeopleThresholdSize* peopleThreshold) :
		BoundingBoxRegulator(peopleThreshold->maxArea, peopleThreshold->maxWidth, peopleThreshold->maxHeight)
	{

	}

	std::vector<cv::Rect> regulateBoxes(const std::vector<cv::Rect>& boxesToRegulate, const std::vector<std::vector<cv::Point>>& convexHullsInOrderOfBoxes) {
		std::vector<cv::Rect> updatedBoxes;
		if (boxesToRegulate.size() != convexHullsInOrderOfBoxes.size()) {
			std::cout << "sizes don't match" << std::endl;
		}

		for (int i = 0; i < boxesToRegulate.size(); i++) {
			const auto box = boxesToRegulate[i];
			const auto convexHull = convexHullsInOrderOfBoxes[i];
			auto regulatedBoxes = regulateBox(box, convexHull);

			updatedBoxes.insert(updatedBoxes.end(), regulatedBoxes.begin(), regulatedBoxes.end());
		}

		return updatedBoxes;
	}

private:
	int maxArea;
	int maxWidth;
	int maxHeight;

	//could pass down convex hull to and split the hulls in half, then redraw the boundingbox based on hull
	std::vector<cv::Rect> regulateBox(const cv::Rect &boxToRegulate, const std::vector<cv::Point>& convexHull) {
		std::vector<cv::Rect> updatedBoxes;
		if (boxToRegulate.width > maxWidth) {
			int splitIntoNParts = int(ceil(boxToRegulate.width / (double)maxWidth));
			int newWidth = boxToRegulate.width / splitIntoNParts;
			int xOfBox = boxToRegulate.x;

			for (int i = 0; i < splitIntoNParts; i++) {
				cv::Rect reducedBox(xOfBox, boxToRegulate.y, newWidth, boxToRegulate.height);
				xOfBox += newWidth;
				updatedBoxes.push_back(getSmallesBoxFromHull(reducedBox, convexHull, true));
			}
		}

		else if (boxToRegulate.height > maxHeight) {
			int splitIntoNParts = int(ceil(boxToRegulate.height / (double)maxHeight));
			int newHeight = boxToRegulate.height / splitIntoNParts;
			int yOfBox = boxToRegulate.y;

			for (int i = 0; i < splitIntoNParts; i++) {
				cv::Rect reducedBox(boxToRegulate.x, yOfBox, boxToRegulate.width, newHeight);
				yOfBox += newHeight;
				updatedBoxes.push_back(getSmallesBoxFromHull(reducedBox, convexHull, false));
			}
		}
		else {
			updatedBoxes.push_back(boxToRegulate);
		}

		return updatedBoxes;
	}

	//TO DO tidy this function up into two functions xaxis and yaxis
	cv::Rect getSmallesBoxFromHull(const cv::Rect& reducedBox, const std::vector<cv::Point>& convexHull, bool splitOnXAxis) {
		int x = splitOnXAxis ? reducedBox.x : -1;
		int brX = splitOnXAxis  ? reducedBox.br().x : -1;
		int y = !splitOnXAxis ? reducedBox.y : -1;
		int brY = !splitOnXAxis ? reducedBox.br().y : -1;

		for (auto point : convexHull) {
			bool ignoreXPoint = splitOnXAxis && point.x < reducedBox.x || point.x > reducedBox.br().x;
			bool ignoreYPoint = !splitOnXAxis && point.y < reducedBox.y || point.y > reducedBox.br().y;

			if (ignoreXPoint || ignoreYPoint) {
				continue;
			}

			if (!splitOnXAxis) {
				x = getSmallestIntFromHull(x, point.x);
				brX = getLargestIntFromHull(brX, point.x);
			}
			else {
				y = getSmallestIntFromHull(y, point.y);
				brY = getLargestIntFromHull(brY, point.y);
			}
		}

		return cv::Rect(x, y, brX - x, brY - y);
	}

	int getSmallestIntFromHull(int currentNum, int numToTry) {
		return currentNum == -1 || numToTry < currentNum ? numToTry : currentNum;
	}

	int getLargestIntFromHull(int currentNum, int numToTry) {
		return numToTry > currentNum ? numToTry : currentNum;
	}
};