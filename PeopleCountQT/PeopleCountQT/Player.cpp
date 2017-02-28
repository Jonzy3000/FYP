#include "Player.h"
#include <chrono>
#include <thread>
#include <QTime>
#include <iostream>

typedef std::chrono::high_resolution_clock Clock;
/*
http://codingexodus.blogspot.co.uk/2012/12/working-with-video-using-opencv-and-qt.html
*/

Player::Player(QObject *parent)
	: QThread(parent)
{
	stop = true;
}

bool Player::loadVideo(std::string filename) {
	capture.open(filename);
	return loadVideo();
}

bool Player::loadVideo(int captureNumber)
{
	capture.open(captureNumber);
	return loadVideo();
}

bool Player::loadVideo()
{
	pBackgroundSubtractionProcessor = std::make_shared<BackgroundSubtractionProcessor>(pCalibrationOptions);
	if (capture.isOpened()) {
		frameRate = (int)capture.get(CV_CAP_PROP_FPS);
		frameRate = frameRate == 0 ? 200 : frameRate;
		Play();
		return true;
	}

	return false;
}


void Player::Play()
{
	if (!isRunning()) {
		if (isStopped()) {
			stop = false;
		}
		start(LowPriority);
	}
}

void Player::run()
{
	while (!stop) {
		int delay = (1000 / frameRate);

		if (!bPaused) {
			if (!capture.read(frame) || frame.empty())
			{
				Stop();
				return;
			}
		}

		auto now = Clock::now();

		//perform algorithm
		//need to create an pausedFrame to use when we're paused so we don't corrupt the original frame
		frame = pBackgroundSubtractionProcessor->process(frame, bPaused);

		delay -= std::chrono::duration_cast<std::chrono::milliseconds>(Clock::now() - now).count();

		if (frame.channels() == 3) {
			cv::cvtColor(frame, RGBframe, CV_BGR2RGB);
			img = QImage((const unsigned char*)(RGBframe.data),
				RGBframe.cols, RGBframe.rows, QImage::Format_RGB888);
		}
		else
		{
			img = QImage((const unsigned char*)(frame.data),
				frame.cols, frame.rows, QImage::Format_Indexed8);
		}

		emit processedImage(img);
		this->msleep(delay);
	}
}

Player::~Player()
{
	mutex.lock();
	stop = true;
	capture.release();
	condition.wakeOne();
	mutex.unlock();
	wait();
}
void Player::Stop()
{
	stop = true;

}
void Player::msleep(int ms) {
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

bool Player::isStopped() const {
	return this->stop;
}

void Player::pause()
{
	bPaused = true;
}

void Player::unpause() {
	bPaused = false;
}

void Player::setCalibrationOptions(const std::shared_ptr<CalibrationOptions>& pCalibrationOptions_) {
	pCalibrationOptions = pCalibrationOptions_;
}

void Player::onImageNameChange(QString imageName_)
{
	pBackgroundSubtractionProcessor->onChangeOfImageToShow(imageName_.toStdString());
}
