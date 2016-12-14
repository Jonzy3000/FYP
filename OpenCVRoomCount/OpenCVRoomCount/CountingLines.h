#pragma once
#include <opencv2/opencv.hpp>
#include "ConfigOptions.h"
#include "stdafx.h"

typedef std::shared_ptr<ConfigOptions::CountingLinesConfig> CountingLinesConfigPtr;
typedef ConfigOptions::CountingLinesConfig::ORIENTATION ORIENTATION;
typedef std::pair<cv::Point, cv::Point> Line;

/*
TODO CALL ENDLINE AND STARTLINE INLINE AND OUTLINE EVERYWHEREREHREHRHE*/

class CountingLines {
public:
	CountingLines(const CountingLinesConfigPtr countingLinesConfig_) : 
		countingLinesConfig(countingLinesConfig_) 
	{

	}

	std::pair<Line, Line> getCountingLines(const cv::Size & sizeOfFrame) {
		if (!bCountingLinesSetup) {
			setupCountingLines(sizeOfFrame);
		}

		return std::make_pair(startLine, endLine);
	}

private:
	CountingLinesConfigPtr countingLinesConfig;
	bool bCountingLinesSetup = false;
	Line startLine;
	Line endLine;

	void setupCountingLines(const cv::Size & sizeOfFrame) {
		const int frameWidth = sizeOfFrame.width;
		const int frameHeight = sizeOfFrame.height;

		const auto orientation = countingLinesConfig->orientation;
		const auto startLinePercent = countingLinesConfig->startLinePerencateOfScreen;
		const auto endLinePercent = countingLinesConfig->endLinePercentageOfScreen;

		if (orientation == ORIENTATION::HORIZONTAL) {
			setupHorizontalLines(frameHeight, frameWidth, startLinePercent, endLinePercent);
		}
		else if (orientation == ORIENTATION::VERTICAL) {
			setupVerticalLines(frameHeight, frameWidth, startLinePercent, endLinePercent);
		}

		bCountingLinesSetup = true;
	}

	void setupHorizontalLines(int frameHeight, int frameWidth, int startLinePercent, int endLinePercent) {
		double startLineHeight = frameHeight * ((double)startLinePercent / 100.0f);
		double endLineHeight = frameHeight * ((double)endLinePercent / 100.0f);

		startLine = std::make_pair(cv::Point(0, startLineHeight), cv::Point(frameWidth, startLineHeight));
		endLine = std::make_pair(cv::Point(0, endLineHeight), cv::Point(frameWidth, endLineHeight));
	}

	void setupVerticalLines(int frameHeight, int frameWidth, int startLinePercent, int endLinePercent) {
		double startLineWidth = frameWidth * ((double)startLinePercent / 100.0f);
		double endLineWidth = frameWidth *  ((double)endLinePercent / 100.0f);

		startLine = std::make_pair(cv::Point(startLineWidth, 0), cv::Point(startLineWidth, frameHeight));
		endLine = std::make_pair(cv::Point(endLineWidth, 0), cv::Point(endLineWidth, frameHeight));
	}
};
