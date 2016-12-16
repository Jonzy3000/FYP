#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include "CountManager.h"
#include "HSIVector.h"
#include <memory>
#include "BoundingBoxUtils.h"

class BoundingBoxTracker {
public:
	enum DIRECTION {
		UP,
		DOWN,
		NONE
	};

	struct TrackedBox {
		TrackedBox(cv::Rect & startPoint_, int frameNumber_, DIRECTION direction_, std::shared_ptr<HSIVector> pHSIVector_) :
			startRect(startPoint_),
			currentBoundingBox(startPoint_),
			frameNumber(frameNumber_),
			direction(direction_),
			pHSIVector(pHSIVector_)
		{

		}

		cv::Rect startRect;
		DIRECTION direction;
		cv::Rect currentBoundingBox;
		int frameNumber;
		std::shared_ptr<HSIVector> pHSIVector;
	};

	void updateCounter(DIRECTION direction) {
		if (direction == DIRECTION::UP) {
			countManger.incrementCountIn();
		}
		else if (direction == DIRECTION::DOWN) {
			countManger.incrementCountOut();
		}
	}

	void trackBoxes(std::vector<cv::Rect> baxoesToTrack, int frameNumber, const cv::Mat & frame_) {
		this->frame = frame_;

		for (auto box : baxoesToTrack) {
			trackBox(box, frameNumber);
		}

		cleanUpBoxesThatHaveNotBeenUpdatedRecently(frameNumber);
	}

	int size() {
		return boxes.size();
	}

	void drawText(cv::Mat& frame) {
		std::string text = "IN: " + std::to_string(countManger.getCountIn()) + " OUT: " + std::to_string(countManger.getCountOut());
		cv::putText(frame, text, cv::Point(100, 100), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(25, 25, 255));
	}

	void drawIDs(cv::Mat& frame) {
		for (auto box : boxes) {
			auto pos = box.second.currentBoundingBox;
			std::string id = "ID: " + std::to_string(box.first);
			cv::putText(frame, id, cv::Point(pos.x, pos.y), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(25, 25, 255));
		}
	}

	void setCountingLines(std::pair<cv::Point, cv::Point> startLine_, std::pair<cv::Point, cv::Point> endLine_) {
		startLine = startLine_;
		endLine = endLine_;
	}

private:
	CountManager countManger = CountManager();
	std::map<int, TrackedBox> boxes;
	std::pair<cv::Point, cv::Point> startLine;
	std::pair<cv::Point, cv::Point> endLine;
	int idOfBox = 0;
	cv::Mat frame;

	void trackBox(cv::Rect box, int frameNumber) {
		bool newBox = true;

		for (auto & trackedBox : boxes) {
			auto currentBox = trackedBox.second.currentBoundingBox;
			//
			if (doBoxesOverlap(currentBox, box)) {
				updateBox(trackedBox.second, box, frameNumber);
				newBox = false;

				if (hasBoxedPassedLine(trackedBox.second)) {
					updateCounter(trackedBox.second.direction);
					trackedBox.second.direction = DIRECTION::NONE;
				}

				break;
			}
		}

		if (newBox) {
			addToBoxes(box, frameNumber);
		}
	}

	bool doColourVecotorsEqual(std::shared_ptr<HSIVector> initial, const cv::Rect box) {
		auto pHSIVector = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));
		return doColourVecotorsEqual(initial, pHSIVector);
	}

	bool doColourVecotorsEqual(std::shared_ptr<HSIVector> initial, std::shared_ptr<HSIVector> other) {
		return initial->equal(*other.get());
	}

	bool hasBoxedPassedLine(TrackedBox & trackedBox) {
		DIRECTION direction = getDirectionOfBoxBasedOnStartingLine(trackedBox.currentBoundingBox);

		if (isBoxAtOppositeLine(direction, trackedBox.direction)) {
			return true;
		}

		return false;
	}

	void updateBox(TrackedBox & trackedBox, cv::Rect box, int frameNumber) {
		if (frameNumber == trackedBox.frameNumber) {
			//mergesplit problem I think, we have two boxes declaring that they're the same box
			std::cout << "MERGE SPLIT PROBLEM" << std::endl;
		}

		//trackedBox.pHSIVector = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));
		trackedBox.currentBoundingBox = box;
		trackedBox.frameNumber = frameNumber;
	}

	void addToBoxes(cv::Rect box, int frameNumber) {
		DIRECTION direction = getDirectionOfBoxBasedOnStartingLine(box);

		if (direction == DIRECTION::NONE) {
			return;
		}

		auto pHSIVector = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));

		boxes.insert(std::make_pair(idOfBox++, TrackedBox(box, frameNumber, direction, pHSIVector)));
	}

	//http://gamedev.stackexchange.com/questions/586/what-is-the-fastest-way-to-work-out-2d-bounding-box-intersection
	bool doBoxesOverlap(cv::Rect box1, cv::Rect box2) {
		return (fabs(box1.x - box2.x) * 2 < box1.width + box2.width &&
			fabs(box1.y - box2.y) * 2 < box1.height + box2.height);
	}

	DIRECTION getDirectionOfBoxBasedOnStartingLine(const cv::Rect & box) {
		if (box.y < endLine.first.y && box.height + box.y > endLine.first.y) {
			return DIRECTION::UP;
		} 
		if (box.y < startLine.first.y && box.height + box.y > startLine.first.y) {
			return DIRECTION::DOWN;
		}

		return DIRECTION::NONE;
	}

	void cleanUpBoxesThatHaveNotBeenUpdatedRecently(int currentFrameNumber) {
		std::vector<int> idsToRemove;
		for (auto trackedBoxes : boxes) {
			if (abs(trackedBoxes.second.frameNumber - currentFrameNumber) > 10) {
				idsToRemove.push_back(trackedBoxes.first);
			}
		}

		removeBoxesBasedOnId(idsToRemove);
	}

	void removeBoxesBasedOnId(std::vector<int> idsOfBoxesToRemove) {
		for (auto idToRemove : idsOfBoxesToRemove) {
			auto itr = boxes.find(idToRemove);
			if (itr != boxes.end()) {
				std::cout << "REMOVING " << idToRemove << std::endl;
				boxes.erase(itr);
			}
		}
	}

	bool isBoxAtOppositeLine(DIRECTION direction, DIRECTION initialDirection) {
		return direction != DIRECTION::NONE && direction != initialDirection;
	}
};
