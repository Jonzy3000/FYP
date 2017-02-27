#pragma once


#include <memory>
#include <QtWidgets/QMainWindow>
#include "ui_PeopleCountQT.h"
#include <QFileDialog>
#include <QMessageBox>
#include <Player.h>
#include "CalibrationOptions.h"
#include "CalibrationLoader.h"
#include "CalibrationSaver.h"

class PeopleCountQT : public QMainWindow
{
	Q_OBJECT

public:
	PeopleCountQT(QWidget *parent = Q_NULLPTR);
	~PeopleCountQT();

private slots:
	//Display video frame in player UI
	void updatePlayerUI(QImage img);
	void onloadVideoClicked();
	void onSaveButtonClicked();

private:
	Ui::PeopleCountQTClass ui;
	std::shared_ptr<Player> pPlayer;
	std::shared_ptr<CalibrationOptions> pCalibrationOptions = std::make_shared<CalibrationOptions>();
	std::shared_ptr<CalibrationLoader> pCalibrationLoader = std::make_shared<CalibrationLoader>();
	void connectCalibrationOptions();
	void connectLoadedCalibrationOptions();
};
