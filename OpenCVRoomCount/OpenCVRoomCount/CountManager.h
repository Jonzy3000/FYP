#pragma once


//https://github.com/corvusoft/restbed

class CountManager {
public:
	void incrementCountIn() {
		countIn++;
	}

	void incrementCountOut() {
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
};
