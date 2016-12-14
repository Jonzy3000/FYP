#pragma once
#include <opencv2/opencv.hpp>
#include "EdgeDetector.h"
#include "ContourFinder.h"
#include "BoundingBoxTracker.h"
#include "ForegroundEstimation.h"

class EdgeFrameDifferentProcessor {
public:
	EdgeFrameDifferentProcessor(cv::VideoCapture & vc_) : vc(vc_)
	{

	}

	void start() {
		cv::Mat frame;
		cv::Mat edgeFrameMOG2, edgeForeground;
		auto pMOG2 = cv::createBackgroundSubtractorMOG2();
		BoundingBoxTracker boundBoxTracker = BoundingBoxTracker();

		while (cvWaitKey(35) != 'q') {
			vc >> frame;
			EdgeDetector edge = EdgeDetector(frame);
			cv::Mat edgeFrame = edge.getEdgeFrame();
			ForegroundEstimation foregroundEstiamtion = ForegroundEstimation();
			int frameNumber = vc.get(CV_CAP_PROP_POS_FRAMES);
			edgeForeground = foregroundEstiamtion.getForeground(edgeFrame, frameNumber);

			pMOG2->apply(edgeForeground, edgeFrameMOG2);

			cv::Mat thresh, morphOpen, morphClose;
			cv::threshold(edgeForeground, thresh, 200, 255, cv::THRESH_BINARY);
			cv::morphologyEx(thresh, morphOpen, cv::MORPH_OPEN, cv::Mat::ones(cv::Size(3, 3), CV_8U));
			cv::morphologyEx(morphOpen, morphClose, cv::MORPH_CLOSE, cv::Mat::ones(cv::Size(11, 11), CV_8U));


			auto contours = ContourFinder(morphClose, 400);
			contours.findContours();

			auto boundingBoxes = contours.getBoundingBoxesOfCountours();
			contours.drawBoundingRects(boundingBoxes, frame);
			//boundBoxTracker.trackBoxes(bondoingBoxes);

			contours.drawContours(frame);


			cv::imshow("morphClose", morphClose);
			cv::imshow("morphOpen", morphOpen);
			cv::imshow("threshold", thresh);
			cv::imshow("frame", frame);
			cv::imshow("edge", edgeForeground);
			cv::imshow("mog", edgeFrameMOG2);
		}
	}
private:
	cv::VideoCapture vc;
};
