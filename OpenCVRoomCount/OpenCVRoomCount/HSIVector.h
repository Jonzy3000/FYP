#pragma once
#include <opencv2/opencv.hpp>
#include <iostream>
#include <functional>

class HSIVector {
public:
	HSIVector(const cv::Mat & boundingBox_) : boundingBox(boundingBox_) {
		hsiModel = cv::Mat(boundingBox.rows, boundingBox.cols, boundingBox.type());
		convertToHSIModel();
		calculateColourVector();
		/*for (auto colour : hueColourVector) {
			std::cout << colour << ", " ;
		}

		std::cout << std::endl;*/
	}

	const std::vector<int> getHueColourVector() {
		return hueColourVector;
	}

	bool equal(HSIVector& other) {
		return other.getHueColourVector() == this->hueColourVector;
	}

private:
	cv::Mat boundingBox;
	cv::Mat hsiModel;
	std::vector<int> hueColourVector;
	std::vector<int> intensityColourVector;

	std::vector<int> hueHistogram;
	std::vector<int> intensityHistogram;

	const float PI = 3.14159265f;

	void convertToHSIModel() {
		float red, green, blue, hue, saturation, intensity;

		for (int i = 0; i < boundingBox.rows; i++) {
			for (int j = 0; j < boundingBox.cols; j++) {
				auto rgb = boundingBox.at<cv::Vec3b>(i, j);
				blue = rgb[0];
				green = rgb[1];
				red = rgb[2];

				intensity = (blue + green + red) / 3;
				auto minValue = std::min(red, std::min(blue, green));

				saturation = 1 - 3 * (minValue / (red + green + blue));

				if (saturation < 0.00001) {
					saturation = 0;
				}
				else if (saturation > 0.99999) {
					saturation = 1;
				}

				if (saturation != 0) {
					hue = 0.5f * ((red - green) + (red - blue)) / sqrt(((red - green) * (red - green)) + (red - blue) * (green - blue));
					hue = acos(hue);

					if (blue <= green) {
						hue = hue;
					}
					else {
						hue = ((360 * PI) / 180.0f) - hue;
					}
				}

				hsiModel.at<cv::Vec3f>(i, j)[0] = (hue * 180) / PI;
				hsiModel.at<cv::Vec3f>(i, j)[1] = saturation * 100.0f;
				hsiModel.at<cv::Vec3f>(i, j)[2] = intensity;
			}
		}
	}

	//we find the hue histogram, if most of the saturation is 0, we then find the intensity colour vector

	void calculateColourVector() {
		caclculateHistogram();
		intensityColourVector = getTheNLargestNumbersFromVector(3, intensityHistogram);
		hueColourVector = getTheNLargestNumbersFromVector(3, hueHistogram);
	}

	std::vector<int> getTheNLargestNumbersFromVector(int n, std::vector<int> vec) {
		std::vector<int> retVal(n), largestNNumbers(n);
		int smallestNumber = 0;
		for (auto deg : vec) {
			if (deg > smallestNumber) {
				largestNNumbers.at(n - 1) = deg;
				smallestNumber = deg;
				std::sort(largestNNumbers.begin(), largestNNumbers.end(), std::greater<int>());
			}
		}

		int j = 0;
		for (auto number : largestNNumbers) {
			int index = std::find(vec.begin(), vec.end(), number) - vec.begin();
			retVal[j++] = index;
		}

		return retVal;
	}

	void caclculateHistogram() {
		calculateIntensityHistogram();
		calculateHueHistogram();
	}

	void calculateIntensityHistogram() {
		intensityHistogram = calculateGenericHistogram(16, 256, false);
	}

	void calculateHueHistogram() {
		hueHistogram = calculateGenericHistogram(10, 360, true);
	}

	std::vector<int> calculateGenericHistogram(const int slicingFactor, const int angles, bool bUseHue) {
		const int slicesOfHistogram = angles / slicingFactor;
		std::vector<int> hist(slicesOfHistogram, 0);

		for (int i = 0; i < hsiModel.rows; i++) {
			for (int j = 0; j < hsiModel.cols; j++)   {
				auto hue = hsiModel.at<cv::Vec3f>(i, j)[0];
				auto intensity = hsiModel.at<cv::Vec3f>(i, j)[2];

				auto colourValue = bUseHue ? hue : intensity;
				colourValue /= slicingFactor;
				colourValue = ceil(colourValue);

				if (colourValue < slicesOfHistogram) {
					hist.at(int(colourValue))++;
				}
			}
		}

		return hist;
	}
};