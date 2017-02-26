#include "Player.h"
#include <chrono>
#include <thread>


/*
http://codingexodus.blogspot.co.uk/2012/12/working-with-video-using-opencv-and-qt.html
*/

Player::Player(QObject *parent)
	: QThread(parent)
{
	stop = true;
}

bool Player::loadVideo(std::string filename) {
	pBackgroundSubtractionProcessor = std::make_shared<BackgroundSubtractionProcessor>(pCalibrationOptions);

	capture.open(filename);
	if (capture.isOpened())
	{
		frameRate = (int)capture.get(CV_CAP_PROP_FPS);
		Play();
		return true;
	}
	else
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
	int delay = (1000 / frameRate);
	while (!stop) {
		if (!capture.read(frame) || frame.empty())
		{
			stop = true;
			return;
		}


		//perform algorithm
		frame = pBackgroundSubtractionProcessor->process(frame);

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

void Player::setCalibrationOptions(const std::shared_ptr<CalibrationOptions>& pCalibrationOptions_) {
	pCalibrationOptions = pCalibrationOptions_;
}
