#pragma once
#include <opencv2/opencv.hpp>
#include "EdgeDetector.h"
#include "ContourFinder.h"
#include "BoundingBoxTracker.h"

class OpticalFlowProcesor {
public:
	OpticalFlowProcesor(cv::VideoCapture & vc_) : vc(vc_)
	{

	}

	void start() {
		cv::Mat frame;
		cv::Mat grayFrame;
		cv::Mat previousGrayFrame, flow;
		cv::UMat flowUmat;
		BoundingBoxTracker boundBoxTracker = BoundingBoxTracker();

		while (cvWaitKey(25) != 'q') {
			vc >> frame;

			if (frame.empty()) {
				break;
			}

			cvtColor(frame, grayFrame, CV_BGR2GRAY);

			if (!previousGrayFrame.empty()) {
				cv::calcOpticalFlowFarneback(previousGrayFrame, grayFrame, flowUmat, 0.4, 1, 12, 2, 8, 1.2, 0);
				flowUmat.copyTo(flow);

				//http://stackoverflow.com/questions/7693561/opencv-displaying-a-2-channel-image-optical-flow
				cv::Mat xy[2];
				cv::split(flow, xy);

				cv::Mat magnitude, angle;
				cv::cartToPolar(xy[0], xy[1], magnitude, angle, true);

				double mag_max;
				cv::minMaxLoc(magnitude, 0, &mag_max);
				magnitude.convertTo(magnitude, -1, 1.0 / mag_max);

				// build hsv image
				cv::Mat _hsv[3], hsv;
				_hsv[0] = angle;
				_hsv[1] = cv::Mat::ones(angle.size(), CV_32F);
				_hsv[2] = magnitude;
				cv::merge(_hsv, 3, hsv);

				//convert to BGR and show
				cv::Mat bgr;//CV_32FC3 matrix
				cv::cvtColor(hsv, bgr, cv::COLOR_HSV2BGR);
				cv::imshow("optical flow", bgr);

				cv::Mat flowWhite = cv::Mat::zeros(magnitude.size(), CV_8U);
				for (int x = 0; x < magnitude.rows; x++) {
					for (int y = 0; y < magnitude.cols; y++) {
						auto mag = magnitude.at<uchar>(x, y);
						if (mag > 275) {
							flowWhite.at<uchar>(x, y) = 255;
						}
					}
				}


				// http://funvision.blogspot.co.uk/2016/02/opencv-31-tutorial-optical-flow.html
				for (int y = 0; y < frame.rows; y += 5) {
					for (int x = 0; x < frame.cols; x += 5) {
						// get the flow from y, x position
						const cv::Point2f flowatxy = flow.at<cv::Point2f>(y, x) * 1000;

						// draw line at flow direction
						cv::line(frame, cv::Point(x, y), cv::Point(cvRound(x + flowatxy.x), cvRound(y + flowatxy.y)), cv::Scalar(255, 0, 0));
						// draw initial point
						cv::circle(frame, cv::Point(x, y), 1, cv::Scalar(0, 0, 0), -1);
					}

				}

				//http://docs.opencv.org/trunk/d7/d8b/tutorial_py_lucas_kanade.html

				cv::imshow("prew", frame);
				cv::imshow("flowWHite", flowWhite);
			}

			grayFrame.copyTo(previousGrayFrame);
		}
	}

private:
	cv::VideoCapture vc;
};