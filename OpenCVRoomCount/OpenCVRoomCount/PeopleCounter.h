#pragma once
#include <opencv2/opencv.hpp>
#include "EdgeDetector.h"
#include "ContourFinder.h"
#include "EdgeFrameDifferentProcessor.h"
#include "OpticalFlowProcessor.h"
#include "BackgroundSubtractionProcessor.h"
#include "JSONReader.h"
class PeopleCounter
{
public:
	void start() {
		cv::VideoCapture vc = cv::VideoCapture("video\\peopleCounter.avi");
		JSONReader jsonReader("../config/config.json");
		auto config = jsonReader.getConfigOptions();
		BackgroundSubtractionProcessor op(vc, config);
		//BackgroundSubtractionProcessor op(vc);
		op.start();
	}
};

/*
Tracking algorithm
Label bounding boxes, (also store direction and start point?)
update bounding boxes, overlap = same bounding box (have these boxes been seen before if not label)
is a bounding box past the line, remove 
*/