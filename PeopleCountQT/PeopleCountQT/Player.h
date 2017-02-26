#pragma once
#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>
#include "BackgroundSubtractionProcessor.h"
#include "CalibrationOptions.h"

using namespace cv;
class Player : public QThread
{
	Q_OBJECT
signals:
	//Signal to output frame to be displayed
	void processedImage(const QImage &image);
protected:
	void run();
	void msleep(int ms);
public:
	//Constructor
	Player(QObject *parent = 0);
	//Destructor
	~Player();
	//Load a video from memory
	bool loadVideo(std::string filename);
	//Play the video
	void Play();
	//Stop the video
	void Stop();
	//check if the player has been stopped
	bool isStopped() const;

	void setCalibrationOptions(const std::shared_ptr<CalibrationOptions> & pCalibrationOptions_);

private:
	bool stop;
	QMutex mutex;
	QWaitCondition condition;
	Mat frame;
	int frameRate;
	VideoCapture capture;
	Mat RGBframe;
	QImage img;
	std::shared_ptr<BackgroundSubtractionProcessor> pBackgroundSubtractionProcessor;
	std::shared_ptr<CalibrationOptions> pCalibrationOptions;
};
