#pragma once
#include <QObject>
#include <QThread>
#include <chrono>
#include <thread>
#include <QMutex>
#include <QWaitCondition>


typedef std::chrono::high_resolution_clock Clock;

class UpdateUniformlyInTime : public QThread {
	Q_OBJECT

protected:
	void run() {
		while (!bAbort) {
			if (hasEnoughTimePassed() && countToSend != 0) {
				int temp = countToSend;
				countToSend = 0;
				timeLastUpdated = Clock::now();
				emit updateCounter(temp);
			}

			msleep(50);
		}
	}

	void msleep(int ms) {
		std::this_thread::sleep_for(std::chrono::milliseconds(ms));
	}

public:
	UpdateUniformlyInTime(QObject* parent)
		: QThread(parent)
	{
		start(LowestPriority);
	}
	
	void updateCountToSend(int count) {
		countToSend += count;
	}

	~UpdateUniformlyInTime() {
		mutex.lock();
		bAbort = true;
		condition.wakeOne();
		mutex.unlock();
		wait();
	}

signals:
	void updateCounter(int);

private:
	bool hasEnoughTimePassed() {
		return std::chrono::duration_cast<std::chrono::seconds>(Clock::now() - timeLastUpdated).count() > 120;
	}

	int countToSend = 0;
	std::chrono::steady_clock::time_point timeLastUpdated = Clock::now();
	bool bAbort = false;
	QMutex mutex;
	QWaitCondition condition;
};
