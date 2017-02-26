#pragma once
#include "CalibrationOptions.h"
#include "JSONReader.h"
#include <qobject.h>

typedef std::pair<cv::Point, cv::Point> line;

class CalibrationLoader : public QObject {
	Q_OBJECT
public:
	CalibrationLoader(QObject *parent = Q_NULLPTR) {

	}

	void load(std::string fileName) {
		auto json = JSONReader::readJson(fileName);

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
			emit contourUpdate((int)minArea);
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

		emit blobExtractionUpdate((int)thresholdValue, (int)openKernelSize, (int)closeKernelSize);
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


		emit countingLinesUpdate(orientation, (int)outLinePercentage, (int)inLinePercentage);
		
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

		emit peopleThresholdSizeUpdate(maxArea, maxWidth, maxHeight);
	}

signals:
	void contourUpdate(int value);
	void blobExtractionUpdate(int thresholdValue, int openKernelSize, int closeKernelSize);
	void countingLinesUpdate(std::string orientation, int outlinePercentage, int inLinePercentage);
	void peopleThresholdSizeUpdate(int maxArea, int maxWidth, int maxHeight);
	void serverSettingsUpdate(std::string, int);

};
