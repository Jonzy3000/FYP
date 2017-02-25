#include "PeopleCountQT.h"

PeopleCountQT::PeopleCountQT(QWidget *parent)
	: QMainWindow(parent)
{
	pPlayer = new Player();
	QObject::connect(pPlayer, &Player::processedImage, this, &PeopleCountQT::updatePlayerUI);
	ui.setupUi(this);
	QObject::connect(ui.loadVideo, &QPushButton::clicked, this, &PeopleCountQT::onloadVideoClicked);
}

void PeopleCountQT::updatePlayerUI(QImage img) {
	if (!img.isNull())
	{
		ui.label->setAlignment(Qt::AlignCenter);
		ui.label->setPixmap(QPixmap::fromImage(img));
	}
}

void PeopleCountQT::onloadVideoClicked() {

	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open Video"), ".",
		tr("Video Files (*.avi *.mpg *.mp4)"));

	if (!filename.isEmpty()) {
		if (!pPlayer->loadVideo(filename.toStdString()))
		{
			QMessageBox msgBox;
			msgBox.setText("The selected video could not be opened!");
			msgBox.exec();
		}
	}
}


PeopleCountQT::~PeopleCountQT()
{
	delete pPlayer;
}
