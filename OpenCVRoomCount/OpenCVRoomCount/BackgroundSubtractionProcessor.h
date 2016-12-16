#pragma once
#include <opencv2/opencv.hpp>
#include "ContourFinder.h"
#include "BoundingBoxTracker.h"
#include "FPSCounter.h"
#include "stdafx.h"
#include "ConfigOptions.h"
#include "CountingLines.h"

/*
TODO - refactor boxes into people, in contour finder
	 - store hull and box in this person object
	 - take the hull of the frame and create a colour vector on that
	 - */

class BackgroundSubtractionProcessor {
public:
	BackgroundSubtractionProcessor(cv::VideoCapture & vc_, std::shared_ptr<ConfigOptions> pConfigOptions_) : 
		vc(vc_), 
		pConfigOptions(pConfigOptions_) {

	}

	void start() {
		cv::Mat frame, frameMOG2;
		auto pMOG2 = cv::createBackgroundSubtractorMOG2();
		BoundingBoxTracker boundingBoxTracker = BoundingBoxTracker();
		int boxesSize = 0;
		FPSCounter fpsCounter = FPSCounter();

		auto minArea = pConfigOptions->getContourConfig()->minArea;
		auto morphOpenKernel = pConfigOptions->getBlobExtractionConfg()->morphOpenKernelSize;
		auto morphCloseKernel = pConfigOptions->getBlobExtractionConfg()->morphCloseKernelSize;
		auto thresholdValue = pConfigOptions->getBlobExtractionConfg()->thresholdValue;

		CountingLines countingLines(pConfigOptions->getCountingLinesConfig());

		while (cvWaitKey(10) != 'q') {
			vc >> frame;

			if (frame.empty()) {
				break;
			}

			auto lines = countingLines.getCountingLines(frame.size());
			auto startLine = lines.first;
			auto endLine = lines.second;
			
			boundingBoxTracker.setCountingLines(startLine, endLine);

			cv::line(frame, startLine.first, startLine.second, cv::Scalar(255, 50, 50));
			cv::line(frame, endLine.first, endLine.second, cv::Scalar(255, 50, 50));

			int frameNumber = vc.get(CV_CAP_PROP_POS_FRAMES);

			pMOG2->apply(frame, frameMOG2);
			cv::Mat thresh, morphOpen, morphClose;
			cv::threshold(frameMOG2, thresh, thresholdValue, 255, cv::THRESH_BINARY);
			cv::morphologyEx(thresh, morphOpen, cv::MORPH_OPEN, cv::Mat::ones(cv::Size(morphOpenKernel, morphOpenKernel), CV_8U));
			cv::morphologyEx(morphOpen, morphClose, cv::MORPH_CLOSE, cv::Mat::ones(cv::Size(morphCloseKernel, morphCloseKernel), CV_8U));

			ContourFinder contourFinder = ContourFinder(morphClose, minArea);
			auto contours = contourFinder.findContours();
			auto boxes = contourFinder.getBoundingBoxesOfCountours();

			contourFinder.drawBoundingRects(boxes, frame);
			contourFinder.drawContours(frame);

			boundingBoxTracker.trackBoxes(boxes, frameNumber, frame);
			boundingBoxTracker.drawIDs(frame);
			boundingBoxTracker.drawText(frame);

			//cv::dilate(frameMOG2, temp, cv::Mat(), cv::Point(-1, -1), 3);
			//cv::erode(temp, temp, cv::Mat(), cv::Point(-1, -1), 6);
			//cv::dilate(temp, temp, cv::Mat(), cv::Point(-1, -1), 3);
			//ContourFinder contourFinder = ContourFinder(temp, 0);
			//contourFinder.findContours();
			//contourFinder.drawContours(temp);

			cv::putText(frame, cv::format("Average FPS=%d", fpsCounter.getFPS()), cv::Point(0, 20), cv::FONT_HERSHEY_PLAIN, 1, cv::Scalar(0, 0, 255));

			cv::imshow("morphClose", morphClose);
			cv::imshow("morphOpen", morphOpen);
			cv::imshow("threshold", thresh);
			cv::imshow("frame", frame);
		}
	}
private:
	cv::VideoCapture vc;
	std::shared_ptr<ConfigOptions> pConfigOptions;
};