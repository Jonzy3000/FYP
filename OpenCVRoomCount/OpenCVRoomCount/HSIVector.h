#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>

class HSIVector {
public:
	HSIVector(cv::Mat & boundingBox_) : boundingBox(boundingBox_) {
		hsiModel = cv::Mat(boundingBox.rows, boundingBox.cols, boundingBox.type());
		convertToHSIModel();
	}

	void convertToHSIModel() {
		float red, green, blue, hue, saturation, intensity;

		for (int i = 0; i < boundingBox.rows; i++) {
			for (int j = 0; j < boundingBox.cols; j++) {
				auto rgb = boundingBox.at<cv::Vec3b>(i, j);
				blue = rgb[0];
				green = rgb[1];
				red = rgb[2];

				intensity = (blue + green + red) / 3;
				int minValue = 0;
				minValue = std::min(red, std::min(blue, green));

				saturation = 1 - 3 * (minValue / (red + green + blue));

				if (saturation < 0.00001) {
					saturation = 0;
				}
				else if (saturation > 0.99999) {
					saturation = 1;
				}

				if (saturation != 0) {
					hue = 0.5 * ((red - green) + (red - blue)) / sqrt(((red - green) * (red - green)) + (red - blue) * (green - blue));
					hue = acos(hue);

					if (blue <= green) {
						hue = hue;
					}
					else {
						hue = ((360 * PI) / 180.0) - hue;
					}
				}

				hsiModel.at<cv::Vec3b>(i, j)[0] = (hue * 180) / PI;
				hsiModel.at<cv::Vec3b>(i, j)[1] = saturation * 100;
				hsiModel.at<cv::Vec3b>(i, j)[2] = intensity;
			}
		}
	}



private:
	cv::Mat boundingBox;
	cv::Mat hsiModel;
	std::vector<float> hueVector;
	std::vector<float> intensityVector;

	const float PI = 3.14159265;
};