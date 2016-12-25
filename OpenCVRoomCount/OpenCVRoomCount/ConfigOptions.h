#pragma once
#include "stdafx.h"
#include <memory>
#include <opencv2/opencv.hpp>
#include "json.h"

using JSONLib = nlohmann::json;
typedef std::pair<cv::Point, cv::Point> line;

class ConfigOptions {
public:
	ConfigOptions(JSONLib json) {
		setupContourConifg(json);
		setupCountingLines(json);
		setupBlobExtractionConfg(json);
		setupPeopleThreshold(json);
	}

	void setupContourConifg(const JSONLib& json) {
		auto contoursItr = json.find("contours");
		if (contoursItr == json.end()) {
			std::cout << "could not find contours" << std::endl;
			return;
		}

		auto contours = *contoursItr;
		if (!contours.is_object()) {
			std::cout << "contours is not an object" << std::endl;
			return;
		}

		auto minAreaItr = contours.find("min area");
		if (minAreaItr == contours.end()) {
			std::cout << "could not find min area" << std::endl;
			return;
		}

		auto minArea = *minAreaItr;
		if (minArea.is_number_integer()) {
			pContourConfig = std::make_shared<ContourConfig>((int) minArea);
		}
	}

	void setupBlobExtractionConfg(const JSONLib& json) {
		auto blobExtractionItr = json.find("blob extraction");
		if (blobExtractionItr == json.end()) {
			return;
		}

		auto blobExtraction = *blobExtractionItr;
		if (!blobExtraction.is_object()) {
			return;
		}

		auto thresholdValueItr = blobExtraction.find("threshold value");
		if (thresholdValueItr == blobExtraction.end()) {
			return;
		}

		auto thresholdValue = *thresholdValueItr;
		if (!thresholdValue.is_number_integer()) {
			return;
		}

		auto openKernelSizeItr = blobExtraction.find("open kernel size");
		if (openKernelSizeItr == blobExtraction.end()) {
			return;
		}

		auto openKernelSize = *openKernelSizeItr;
		if (!openKernelSize.is_number_integer()) {
			return;
		}

		auto closeKernelSizeItr = blobExtraction.find("close kernel size");
		if (closeKernelSizeItr == blobExtraction.end()) {
			return;
		}

		auto closeKernelSize = *closeKernelSizeItr;
		if (!closeKernelSize.is_number_integer()) {
			return;
		}

		pBlobExtractionConfig = std::make_shared<BlobExtractionConfig>((int) thresholdValue, (int) openKernelSize, (int) closeKernelSize);
	}

	void setupCountingLines(const JSONLib& json) {
		auto countLinesItr = json.find("count lines");
		if (countLinesItr == json.end()) {
			return;
		}

		auto countLines = *countLinesItr;
		if (!countLines.is_object()) {
			return;
		}

		auto orientationItr = countLines.find("oreientation (horizontal or vertical)");
		if (orientationItr == countLines.end()) {
			return;
		}

		auto orientation = *orientationItr;
		if (!orientation.is_string()) {
			return;
		}

		//split up
		auto inLineItr = countLines.find("in line");
		if (inLineItr == countLines.end()) {
			std::cout << "Cannot find 'in line'" << std::endl;
			return;
		}

		auto inLine = *inLineItr;
		if (!inLine.is_object()) {
			return;
		}

		auto inLinePercentageItr = inLine.find("percentage of screen");
		if (inLinePercentageItr == inLine.end()) {
			return;
		}

		auto inLinePercentage = *inLinePercentageItr;
		if (!inLinePercentage.is_number_integer()) {
			return;
		}

		auto outLineItr = countLines.find("out line");
		if (outLineItr == countLines.end()) {
			std::cout << "Cannot find 'out line'" << std::endl;
			return;
		}

		auto outLine = *outLineItr;
		if (!outLine.is_object()) {
			return;
		}

		auto outLinePercentageItr = outLine.find("percentage of screen");
		if (outLinePercentageItr == outLine.end()) {
			return;
		}

		auto outLinePercentage = *outLinePercentageItr;
		if (!outLinePercentage.is_number_integer()) {
			return;
		}


		pCountingLinesConfig = std::make_shared<CountingLinesConfig>(orientation, (int) outLinePercentage, (int) inLinePercentage);
		std::cout << "set up countinglines correctly" << std::endl;
	}

	void setupPeopleThreshold(const JSONLib& json) {
		auto peopleThresholdItr = json.find("people threshold size");
		if (peopleThresholdItr == json.end()) {
			return;
		}

		auto peopleThreshold = *peopleThresholdItr;
		if (!peopleThreshold.is_object()) {
			return;
		}

		auto maxAreaItr = peopleThreshold.find("max area");
		if (maxAreaItr == peopleThreshold.end()) {
			return;
		}

		auto maxArea = *maxAreaItr;
		if (!maxArea.is_number_integer()) {
			return;
		}

		auto maxWidthItr = peopleThreshold.find("max width");
		if (maxWidthItr == peopleThreshold.end()) {
			return;
		}

		auto maxWidth = *maxWidthItr;
		if (!maxWidth.is_number_integer()) {
			return;
		}

		auto maxHeightItr = peopleThreshold.find("max height");
		if (maxHeightItr == peopleThreshold.end()) {
			return;
		}

		auto maxHeight = *maxHeightItr;
		if (!maxHeight.is_number_integer()) {
			return;
		}

		pPopleThresholdSize = std::make_shared<PeopleThresholdSize>(maxArea, maxWidth, maxHeight);
	}

	

	struct ContourConfig {
		ContourConfig(int minArea_) : 
			minArea(minArea_) 
		{

		}

		const int minArea;
	};

	struct BlobExtractionConfig {
		BlobExtractionConfig(int thresholdValue_, int morphOpenKernelSize_, int morphCloseKernelSize_) :
			thresholdValue(thresholdValue_),
			morphOpenKernelSize(morphOpenKernelSize_),
			morphCloseKernelSize(morphCloseKernelSize_)
		{

		}

		const int thresholdValue;
		const int morphOpenKernelSize;
		const int morphCloseKernelSize;
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
			if (strOrientation == "horizontal") {
				orientation = ORIENTATION::HORIZONTAL;
			}
			else if (strOrientation == "vertical") {
				orientation = ORIENTATION::VERTICAL;
			}
		}

		//CountingLinesConfig(line inLine_, line outLine_) :
		//	inLine(inLine_),
		//	outLine(outLine_)
		//{

		//}

		ORIENTATION orientation = ORIENTATION::VERTICAL;
		const int outLinePercentageOfScreen = 33;
		const int inLinePerencateOfScreen = 66;

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

		const int maxArea;
		const int maxWidth;
		const int maxHeight;
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

private:
	std::shared_ptr<ContourConfig> pContourConfig;
	std::shared_ptr<BlobExtractionConfig> pBlobExtractionConfig;
	std::shared_ptr<PeopleThresholdSize> pPopleThresholdSize;
	std::shared_ptr<CountingLinesConfig>  pCountingLinesConfig;
};
