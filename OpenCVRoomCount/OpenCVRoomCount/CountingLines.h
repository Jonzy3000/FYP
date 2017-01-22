#pragma once
#include <opencv2/opencv.hpp>
#include "ConfigOptions.h"
#include "stdafx.h"
#include "Direction.h"

typedef std::shared_ptr<ConfigOptions::CountingLinesConfig> CountingLinesConfigPtr;
typedef ConfigOptions::CountingLinesConfig::ORIENTATION ORIENTATION;
typedef std::pair<cv::Point, cv::Point> Line;

/*
TODO CALL outLine AND inLine INLINE AND OUTLINE EVERYWHEREREHREHRHE*/

class CountingLines {
public:
	enum TOUCHING_LINE {
		INLINE,
		OUTLINE,
		NONE
	};

	CountingLines(const CountingLinesConfigPtr countingLinesConfig_) :
		countingLinesConfig(countingLinesConfig_)
	{

	}

	std::pair<Line, Line> getCountingLines(const cv::Size & sizeOfFrame) {
		if (!bCountingLinesSetup) {
			setupCountingLines(sizeOfFrame);
		}

		return std::make_pair(inLine, outLine);
	}

	TOUCHING_LINE whichLineIsBoxTouching(const cv::Rect & box, const cv::Size & frameSize, bool bCheckVisiblity) {
		if (!allOfBoxIsVisible(box, frameSize)) {
			return TOUCHING_LINE::NONE; 
		}

		if (countingLinesConfig->HORIZONTAL) {
			return whichLineIsBoxTouchingBasedOnHorizontalLine(box, frameSize);
		}
		else if (countingLinesConfig->VERTICAL) {
			return whichLineIsBoxTouchingBasedOnVerticalLine(box, frameSize);
		}

		return TOUCHING_LINE::NONE;
	}

private:
	CountingLinesConfigPtr countingLinesConfig;
	bool bCountingLinesSetup = false;
	Line inLine;
	Line outLine;

	void setupCountingLines(const cv::Size & sizeOfFrame) {
		const int frameWidth = sizeOfFrame.width;
		const int frameHeight = sizeOfFrame.height;

		const auto orientation = countingLinesConfig->orientation;
		const auto inLinePercent = countingLinesConfig->inLinePerencateOfScreen;
		const auto outLinePercent = countingLinesConfig->outLinePercentageOfScreen;

		if (orientation == ORIENTATION::HORIZONTAL) {
			setupHorizontalLines(frameHeight, frameWidth, inLinePercent, outLinePercent);
		}
		else if (orientation == ORIENTATION::VERTICAL) {
			setupVerticalLines(frameHeight, frameWidth, inLinePercent, outLinePercent);
		}

		bCountingLinesSetup = true;
	}

	void setupHorizontalLines(int frameHeight, int frameWidth, int inLinePercent, int outLinePercent) {
		int inLineHeight = frameHeight * inLinePercent / 100;
		int outLineHeight = frameHeight * outLinePercent / 100;

		inLine = std::make_pair(cv::Point(0, inLineHeight), cv::Point(frameWidth, inLineHeight));
		outLine = std::make_pair(cv::Point(0, outLineHeight), cv::Point(frameWidth, outLineHeight));
	}

	void setupVerticalLines(int frameHeight, int frameWidth, int inLinePercent, int outLinePercent) {
		int inLineWidth = frameWidth * inLinePercent / 100;
		int outLineWidth = frameWidth *  outLinePercent / 100;

		inLine = std::make_pair(cv::Point(inLineWidth, 0), cv::Point(inLineWidth, frameHeight));
		outLine = std::make_pair(cv::Point(outLineWidth, 0), cv::Point(outLineWidth, frameHeight));
	}

	TOUCHING_LINE whichLineIsBoxTouchingBasedOnHorizontalLine(const cv::Rect & box, const cv::Size & frameSize) {
		if (box.x < outLine.first.x && box.width + box.x > outLine.first.x) {
			return TOUCHING_LINE::OUTLINE;
		}
		if (box.x < inLine.first.x && box.width + box.x > inLine.first.x) {
			return TOUCHING_LINE::INLINE;
		}

		return TOUCHING_LINE::NONE;
	}

	TOUCHING_LINE whichLineIsBoxTouchingBasedOnVerticalLine(const cv::Rect & box, const cv::Size & frameSize) {
		if (box.y < outLine.first.y && box.height + box.y > outLine.first.y) {
			return TOUCHING_LINE::OUTLINE;
		}
		if (box.y < inLine.first.y && box.height + box.y > inLine.first.y) {
			return TOUCHING_LINE::INLINE;
		}

		return TOUCHING_LINE::NONE;
	}

	bool allOfBoxIsVisible(const cv::Rect & box, const cv::Size & frameSize) {
		return box.x > 0 && box.y > 0 && box.br().x < frameSize.width && box.br().y < frameSize.height;
	}
};
