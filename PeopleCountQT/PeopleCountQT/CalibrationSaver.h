#pragma once
#include "CalibrationOptions.h"
#include "JSONWriter.h"

class CalibrationSaver {
public:
	CalibrationSaver( const std::shared_ptr<CalibrationOptions> & pCalibrationOptions) :
		pCalibrationOptions(pCalibrationOptions)
	{

	}

	bool saveJson(std::string fileName) {
		JSONLib json;
		json = getContourConfigJSON(json);
		json = getCountingLinesJSON(json);
		json = getPeopleThreshold(json);
		json = getBlobExtractionConfigJSON(json);

		try {
			JSONWriter::saveJson(fileName, json);
		}
		catch (std::exception e) {
			return false;
		}

		return true;
	}

private:
	const std::shared_ptr<CalibrationOptions> pCalibrationOptions;

	JSONLib getContourConfigJSON(JSONLib& json) {
		json["contours"]["min area"] = pCalibrationOptions->getContourConfig()->minArea;
		return json;
	}

	JSONLib getBlobExtractionConfigJSON(JSONLib& json) {
		const auto blobExtractionConfig = pCalibrationOptions->getBlobExtractionConfg();

		json["blob extraction"]["threshold value"] = blobExtractionConfig->thresholdValue;
		json["blob extraction"]["open kernel size"] = blobExtractionConfig->morphOpenKernelSize;
		json["blob extraction"]["close kernel size"] = blobExtractionConfig->morphCloseKernelSize;

		return json;
	}

	JSONLib getCountingLinesJSON(JSONLib& json) {
		const auto countingLinesConfig = pCalibrationOptions->getCountingLinesConfig();
		
		json["count lines"]["oreientation (horizontal or vertical)"] = countingLinesConfig->orientationToString();
		json["count lines"]["inline"]["percentage of screen"] = countingLinesConfig->inLinePerencateOfScreen;
		json["count lines"]["outline"]["percentage of screen"] = countingLinesConfig->outLinePercentageOfScreen;

		return json;
	}

	JSONLib getPeopleThreshold(JSONLib& json) {
		const auto peopleThresholdConfig = pCalibrationOptions->getPeopleThresholdSize();
		
		json["people threshold size"]["max width"] = peopleThresholdConfig->maxWidth;
		json["people threshold size"]["max height"] = peopleThresholdConfig->maxHeight;

		return json;
	}

};