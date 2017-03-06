#pragma once
#include "CalibrationOptions.h"
#include "HttpPostRequests.h"


//https://github.com/corvusoft/restbed

class CountManager {
public:
	CountManager(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions)
	{
		pHttpPostRequests = std::make_shared<HttpPostRequests>(pCalibrationOptions);
		pHttpPostRequests->newRoom("Matts room", 25);
		pHttpPostRequests->newRoom("Matts room", 25);
	}

	void incrementCountIn() {
		pHttpPostRequests->updateCounter("Matts room", 1);
		countIn++;
	}

	void incrementCountOut() {
		pHttpPostRequests->updateCounter("Matts room", -1);
		countOut++;
	}

	int getCountIn() {
		return countIn;
	}

	int getCountOut() {
		return countOut;
	}

private:
	int countIn = 0;
	int countOut = 0;

	std::shared_ptr<HttpPostRequests> pHttpPostRequests;
};
