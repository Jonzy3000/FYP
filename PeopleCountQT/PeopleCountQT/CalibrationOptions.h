#pragma once

#include <memory>
#include <opencv2/opencv.hpp>
#include "qobject.h"

typedef std::pair<cv::Point, cv::Point> line;

class CalibrationOptions : public QObject {
	Q_OBJECT
public:
	CalibrationOptions(QObject *parent = Q_NULLPTR) {

	}

	struct ContourConfig {
		ContourConfig(int minArea_) :
			minArea(minArea_)
		{

		}

		ContourConfig() {}

		int minArea;
	};

	struct BlobExtractionConfig {
		BlobExtractionConfig(int thresholdValue_, int morphOpenKernelSize_, int morphCloseKernelSize_) :
			thresholdValue(thresholdValue_),
			morphOpenKernelSize(morphOpenKernelSize_),
			morphCloseKernelSize(morphCloseKernelSize_)
		{

		}

		BlobExtractionConfig() {}

		int thresholdValue;
		int morphOpenKernelSize;
		int morphCloseKernelSize;
	};

	struct CountingLinesConfig {
		enum ORIENTATION {
			HORIZONTAL,
			VERTICAL
		};

		CountingLinesConfig(std::string strOrientation, int outLinePercentageOfScreen_, int inLinePerencateOfScreen_) :
			outLinePercentageOfScreen(outLinePercentageOfScreen_),
			inLinePerencateOfScreen(inLinePerencateOfScreen_)
		{
			setOrientationWithString(strOrientation);
		}

		CountingLinesConfig() {}

		//CountingLinesConfig(line inLine_, line outLine_) :
		//	inLine(inLine_),
		//	outLine(outLine_)
		//{

		//}
		void setOrientationWithString(std::string strOrientation) {
			if (strOrientation == "horizontal") {
				orientation = ORIENTATION::HORIZONTAL;
			}
			else if (strOrientation == "vertical") {
				orientation = ORIENTATION::VERTICAL;
			}
		}

		std::string orientationToString() {
			switch (orientation) {
			case ORIENTATION::VERTICAL:
				return "vertical";
			case ORIENTATION::HORIZONTAL:
				return "horizontal";
			}

			return "vertical";
		}

		ORIENTATION orientation = ORIENTATION::VERTICAL;
		int outLinePercentageOfScreen = 33;
		int inLinePerencateOfScreen = 66;

		//const line outLine;
		//const line inLine;
	};

	struct PeopleThresholdSize {
		PeopleThresholdSize(int maxArea_, int maxWidth_, int maxHeight_) :
			maxArea(maxArea_),
			maxWidth(maxWidth_),
			maxHeight(maxHeight_)
		{

		}

		PeopleThresholdSize() {}

		int maxArea;
		int maxWidth;
		int maxHeight;
	};

	const std::shared_ptr<ContourConfig> getContourConfig() {
		return pContourConfig;
	}

	const std::shared_ptr<BlobExtractionConfig> getBlobExtractionConfg() {
		return pBlobExtractionConfig;
	}

	const std::shared_ptr<PeopleThresholdSize> getPeopleThresholdSize() {
		return pPopleThresholdSize;
	}

	const std::shared_ptr<CountingLinesConfig> getCountingLinesConfig() {
		return pCountingLinesConfig;
	}

public slots:
	void setupContourConfig(int minArea) {
		pContourConfig = std::make_shared<ContourConfig>(minArea);
	}

	void setupBlobExtractionConfig(int thresholdValue, int morphOpenKernelSize, int morphCloseKernelSize) {
		pBlobExtractionConfig = std::make_shared<BlobExtractionConfig>(thresholdValue, morphOpenKernelSize, morphCloseKernelSize);
	}

	void setupPeopleThresholdSize(int maxArea, int maxWidth, int maxHeight) {
		pPopleThresholdSize = std::make_shared<PeopleThresholdSize>(maxArea, maxWidth, maxHeight);
	}

	void setupCountingLinesConfig(std::string strOrientation, int outLinePercentageOfScreen_, int inLinePerencateOfScreen_) {
		pCountingLinesConfig = std::make_shared<CountingLinesConfig>(strOrientation, outLinePercentageOfScreen_, inLinePerencateOfScreen_);
	}

private:
	std::shared_ptr<ContourConfig> pContourConfig = std::make_shared<ContourConfig>();
	std::shared_ptr<BlobExtractionConfig> pBlobExtractionConfig = std::make_shared<BlobExtractionConfig>();
	std::shared_ptr<PeopleThresholdSize> pPopleThresholdSize = std::make_shared<PeopleThresholdSize>();
	std::shared_ptr<CountingLinesConfig>  pCountingLinesConfig = std::make_shared<CountingLinesConfig>();

};

