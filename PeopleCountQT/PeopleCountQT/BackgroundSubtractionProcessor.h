#pragma once
#include <opencv2/opencv.hpp>
#include "CalibrationOptions.h"

class BackgroundSubtractionProcessor {
public: 
	BackgroundSubtractionProcessor(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions_) :
		pCalibrationOptions(pCalibrationOptions_)
	{
		pMOG2 = cv::createBackgroundSubtractorMOG2();
	}

	cv::Mat process(cv::Mat & frame) {
		cv::Mat frameMOG2;
		pMOG2->apply(frame, frameMOG2);

		auto minArea = pCalibrationOptions->getContourConfig()->minArea;
		auto morphOpenKernel = pCalibrationOptions->getBlobExtractionConfg()->morphOpenKernelSize;
		auto morphCloseKernel = pCalibrationOptions->getBlobExtractionConfg()->morphCloseKernelSize;
		auto thresholdValue = pCalibrationOptions->getBlobExtractionConfg()->thresholdValue;

		cv::Mat thresh, morphOpen, morphClose;
		cv::threshold(frameMOG2, thresh, thresholdValue, 255, cv::THRESH_BINARY);
		cv::morphologyEx(thresh, morphOpen, cv::MORPH_OPEN, cv::Mat::ones(cv::Size(morphOpenKernel, morphOpenKernel), CV_8U));
		cv::morphologyEx(morphOpen, morphClose, cv::MORPH_CLOSE, cv::Mat::ones(cv::Size(morphCloseKernel, morphCloseKernel), CV_8U));


		return thresh;
	}

	void onChangeOfImageToShow(std::string imageToShow_) {
		imageToShow = imageToShow_;
	}

private:
	cv::Ptr<cv::BackgroundSubtractorMOG2> pMOG2;
	const std::shared_ptr<CalibrationOptions> pCalibrationOptions;

	std::string imageToShow;

};