#pragma once
#include <opencv2/opencv.hpp>
#include "CalibrationOptions.h"
#include "ContourFinder.h"
#include "BoundingBoxTracker.h"
#include "FPSCounter.h"
#include "CountingLines.h"
#include "BoundingBoxRegulator.h"

class BackgroundSubtractionProcessor {
public: 
	BackgroundSubtractionProcessor(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions_) :
		pCalibrationOptions(pCalibrationOptions_)
	{
		pMOG2 = cv::createBackgroundSubtractorMOG2();
		pBoundingBoxTracker = std::make_shared<BoundingBoxTracker>(pCalibrationOptions);
	}

	std::pair<const cv::Mat, int> process(cv::Mat & frame, bool isPaused) {
		cv::Mat frameToProcess = frame.clone();

		if (!isPaused) {
			pMOG2->apply(frameToProcess, frameMOG2);
		}

		CountingLines countingLines(pCalibrationOptions->getCountingLinesConfig());
		auto lines = countingLines.getCountingLines(frameToProcess.size());
		auto inLine = lines.first;
		auto outLine = lines.second;
		pBoundingBoxTracker->setCountingLines(countingLines);

		auto minArea = pCalibrationOptions->getContourConfig()->minArea;
		auto morphOpenKernel = pCalibrationOptions->getBlobExtractionConfg()->morphOpenKernelSize;
		auto morphCloseKernel = pCalibrationOptions->getBlobExtractionConfg()->morphCloseKernelSize;
		auto thresholdValue = pCalibrationOptions->getBlobExtractionConfg()->thresholdValue;

		cv::threshold(frameMOG2, thresh, thresholdValue, 255, cv::THRESH_BINARY);
		cv::morphologyEx(thresh, morphOpen, cv::MORPH_OPEN, cv::Mat::ones(cv::Size(morphOpenKernel, morphOpenKernel), CV_8U));
		cv::morphologyEx(morphOpen, morphClose, cv::MORPH_CLOSE, cv::Mat::ones(cv::Size(morphCloseKernel, morphCloseKernel), CV_8U));

		ContourFinder contourFinder = ContourFinder(morphClose, minArea);
		auto contours = contourFinder.findContours();
		auto boxes = contourFinder.getBoundingBoxesOfCountours();
		auto convexHulls = contourFinder.getConvexHulls();

		BoundingBoxRegulator boundBoxRegulator(pCalibrationOptions->getPeopleThresholdSize().get());
		auto regulatedBoxes = boundBoxRegulator.regulateBoxes(boxes, convexHulls);

		contourFinder.drawBoundingRects(regulatedBoxes, frameToProcess);
		contourFinder.drawContours(frameToProcess);
		contourFinder.drawConvexHulls(frameToProcess, convexHulls);

		frameNumber++;
		int counter = pBoundingBoxTracker->trackBoxes(regulatedBoxes, frameNumber, frameToProcess);
		pBoundingBoxTracker->drawIDs(frameToProcess);
		pBoundingBoxTracker->drawText(frameToProcess);

		cv::line(frameToProcess, inLine.first, inLine.second, cv::Scalar(35.0, 255.0, 35.0), 2);
		cv::putText(frameToProcess, "In Line", inLine.first, cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(25, 25, 255));

		cv::line(frameToProcess, outLine.first, outLine.second, cv::Scalar(35.0, 255.0, 35.0), 2);
		cv::putText(frameToProcess, "Out Line", outLine.first, cv::HersheyFonts::FONT_HERSHEY_PLAIN, 1.5, cv::Scalar(25, 25, 255));

		cv::putText(frameToProcess, cv::format("Average FPS=%d", fpsCounter.getFPS()), cv::Point(0, 20), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));


		return std::make_pair(getImageToShow(frameToProcess), counter);
	}

	const cv::Mat getImageToShow(const cv::Mat & frame) {
		if (imageToShow == "Output") {
			return frame;
		} 
		if (imageToShow == "Threshold") {
			return thresh;
		}
		if (imageToShow == "Background Subtraction") {
			return frameMOG2;
		}
		if (imageToShow == "Morph Open") {
			return morphOpen;
		}
		if (imageToShow == "Morph Close") {
			return morphClose;
		}

		return frame;
	}

	void onChangeOfImageToShow(std::string imageToShow_) {
		imageToShow = imageToShow_;
	}

private:
	cv::Mat thresh, morphOpen, morphClose, frameMOG2;
	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2;
	const std::shared_ptr<CalibrationOptions> pCalibrationOptions;
	FPSCounter fpsCounter = FPSCounter();

	std::shared_ptr<BoundingBoxTracker> pBoundingBoxTracker;

	int frameNumber = 0;

	std::string imageToShow;

};