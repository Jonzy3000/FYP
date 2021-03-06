#pragma once
#include <opencv2/opencv.hpp>
#include <math.h>
#include "CountManager.h"
#include "HSIVector.h"
#include <memory>
#include "BoundingBoxUtils.h"
#include "CountingLines.h"
#include "Direction.h"

typedef CountingLines::TOUCHING_LINE TOUCHING_LINE;

class BoundingBoxTracker {
public:
	BoundingBoxTracker(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions_) :
		pCalibrationOptions(pCalibrationOptions_)
	{
		pCountManager = std::make_shared<CountManager>();
	}

	struct TrackedBox {
		TrackedBox(const cv::Rect & startPoint_, int frameNumber_, TOUCHING_LINE direction_, const std::shared_ptr<HSIVector> pHSIVector_) :
			startRect(startPoint_),
			currentBoundingBox(startPoint_),
			frameNumber(frameNumber_),
			direction(direction_),
			pHSIVector(pHSIVector_)
		{

		}

		cv::Rect startRect;
		TOUCHING_LINE direction;
		cv::Rect currentBoundingBox;
		int frameNumber;
		std::shared_ptr<HSIVector> pHSIVector;
	};

	int trackBoxes(std::vector<cv::Rect> baxoesToTrack, int frameNumber, const cv::Mat & frame_) {
		this->frame = frame_;
		int counter = 0;
		for (auto box : baxoesToTrack) {
			counter += trackBox(box, frameNumber);
		}

		cleanUpBoxesThatHaveNotBeenUpdatedRecently(frameNumber);
		return counter;
	}

	int size() {
		return boxes.size();
	}

	void drawText(cv::Mat& frame) {
		std::string IN = " IN: " + std::to_string(pCountManager->getCountIn());
		std::string OUT = "OUT: " + std::to_string(pCountManager->getCountOut());
		cv::putText(frame, IN, cv::Point(frame.cols - 100, 25), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(25, 25, 255));
		cv::putText(frame, OUT, cv::Point(frame.cols - 100, 55), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(25, 25, 255));
	}

	void drawIDs(cv::Mat& frame) {
		for (auto box : boxes) {
			auto pos = box.second.currentBoundingBox;
			std::string id = "ID: " + std::to_string(box.first);
			cv::putText(frame, id, cv::Point(pos.x, pos.y), cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1, cv::Scalar(25, 25, 255));
		}
	}

	void setCountingLines(const CountingLines & countingLines_) {
		pCountingLines = std::make_shared<CountingLines>(countingLines_);
	}

private:
	std::shared_ptr<CountManager> pCountManager;
	std::map<int, TrackedBox> boxes;
	std::shared_ptr<CountingLines> pCountingLines;
	int idOfBox = 0;
	cv::Mat frame;
	std::shared_ptr<CalibrationOptions> pCalibrationOptions;

	int trackBox(cv::Rect box, int frameNumber) {
		bool newBox = true;
		int counter = 0;
		for (auto & trackedBox : boxes) {
			auto currentBox = trackedBox.second.currentBoundingBox;

			if (!isSameTrackedBox(currentBox, box)) {
				continue;
			}

			updateBox(trackedBox.second, box, frameNumber);
			newBox = false;

			if (hasBoxedPassedLine(trackedBox.second)) {
				counter += updateCounter(trackedBox.second.direction);
				trackedBox.second.direction = TOUCHING_LINE::NONE;
			}

			break;
		}

		if (newBox) {
			addToBoxes(box, frameNumber);
		}

		return counter;	
	}

	bool isThereAValidColourVector(TrackedBox box) {
		return box.pHSIVector != nullptr;
	}

	bool doColourVecotorsEqual(std::shared_ptr<HSIVector> initial, const cv::Rect box) {
		auto pHSIVector = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));
		return doColourVecotorsEqual(initial, pHSIVector);
	}

	bool doColourVecotorsEqual(std::shared_ptr<HSIVector> initial, std::shared_ptr<HSIVector> other) {
		return initial->equal(*other.get());
	}

	bool hasBoxedPassedLine(TrackedBox & trackedBox) {
		TOUCHING_LINE direction = whichLineIsBoxTouching(trackedBox.currentBoundingBox);

		if (isBoxAtOppositeLine(direction, trackedBox.direction)) {
			return true;
		}

		return false;
	}

	void updateBox(TrackedBox & trackedBox, cv::Rect box, int frameNumber) {
		//trackedBox.pHSIVector = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));
		trackedBox.currentBoundingBox = box;
		trackedBox.frameNumber = frameNumber;
	}

	void addToBoxes(cv::Rect box, int frameNumber) {
		TOUCHING_LINE direction = whichLineIsBoxTouching(box);

		if (direction == TOUCHING_LINE::NONE) {
			return;
		}

		auto pHSI = std::make_shared<HSIVector>(BoundingBoxUtils::getImageFromBox(frame, box));
		boxes.insert(std::make_pair(idOfBox++, TrackedBox(box, frameNumber, direction, pHSI)));
	}

	bool centersWithinAcceptableDistances(const cv::Rect& box1, const cv::Rect& box2) {
		return BoundingBoxUtils::getDistanceOfCentersBoxes(box1, box2) < 16;
	}

	//http://stackoverflow.com/questions/306316/determine-if-two-rectangles-overlap-each-other
	bool doBoxesOverlap(const cv::Rect& box1, const cv::Rect& box2) {
		return box1.x < box2.br().x
			&& box1.br().x > box2.x
			&& box1.y < box2.br().y
			&& box1.br().y > box2.y;
	}


	bool isSameTrackedBox(const cv::Rect& box1, const cv::Rect& box2) {
		return doBoxesOverlap(box1, box2) && centersWithinAcceptableDistances(box1, box2);
	}

	TOUCHING_LINE whichLineIsBoxTouching(const cv::Rect & box) {
		return pCountingLines->whichLineIsBoxTouching(box, frame.size(), true);
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

	bool isBoxAtOppositeLine(TOUCHING_LINE direction, TOUCHING_LINE initialDirection) {
		return direction != TOUCHING_LINE::NONE && direction != initialDirection;
	}

	int updateCounter(TOUCHING_LINE initialLine) {
		if (initialLine == TOUCHING_LINE::OUTLINE) {
			pCountManager->incrementCountIn();
			return 1;
		}
		else if (initialLine == TOUCHING_LINE::INLINE) {
			pCountManager->incrementCountOut();
			return -1;
		}

		return 0;
	}

	//This should be own class
	bool isThereAMergeSplitProblem(const cv::Rect & currentBox, const cv::Rect & newBox) {
		return (fabs(currentBox.area() - newBox.area()) > 50);
	}

	void processMergeSplitProblem(const cv::Rect & currentBox, const cv::Rect & newBox) {
		if (currentBox.area() > newBox.area()) {
			processSplitProblem(currentBox, newBox);
		}
		else if (newBox.area() > currentBox.area()) {
			processMergeProblem(currentBox, newBox);
		}
	}

	void processMergeProblem(const cv::Rect & currentBox, const cv::Rect & newBox) {

	}

	void processSplitProblem(const cv::Rect & currentBox, const cv::Rect & newBox) {

	}
};
