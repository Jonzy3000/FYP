#pragma once
#include <ctime>
class FPSCounter {
public:
	FPSCounter() {
		frameCounter = 0;
		tick = 0;
		timeBegin = std::time(0);
	}

	int getFPS() {
		frameCounter++;
		std::time_t timeNow = std::time(0) - timeBegin;

		if (timeNow - tick >= 1)
		{
			tick++;
			fps = frameCounter;
			frameCounter = 0;
		}

		return fps;
	}

private:
	int frameCounter, tick, fps;
	std::time_t timeBegin;



};
