#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PeopleCountQT.h"
#include <QFileDialog>
#include <QMessageBox>
#include <Player.h>

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

private:
	Ui::PeopleCountQTClass ui;
	Player* pPlayer;
};
