#include "PeopleCountQT.h"

PeopleCountQT::PeopleCountQT(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	pPlayer = std::make_shared<Player>();
	connectCalibrationOptions();
	connectLoadedCalibrationOptions();

	pCalibrationLoader->load("Calibration\\Calibration.json");

	QObject::connect(ui.captureNumber, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &PeopleCountQT::onCaptureChange);
	QObject::connect(ui.saveButton, &QPushButton::pressed, this, &PeopleCountQT::onSaveButtonClicked);
	QObject::connect(ui.liveCameraFeedCheckBox, &QCheckBox::clicked, this, &PeopleCountQT::onLiveCameraFeedPressed);
	QObject::connect(pPlayer.get(), &Player::processedImage, this, &PeopleCountQT::updatePlayerUI);
	QObject::connect(ui.loadVideo, &QPushButton::clicked, this, &PeopleCountQT::onloadVideoClicked);
	QObject::connect(ui.playPauseButton, &QPushButton::clicked, this, &PeopleCountQT::onPlayPauseButtonClicked);
	pPlayer->setCalibrationOptions(pCalibrationOptions);
}

void PeopleCountQT::updatePlayerUI(QImage img) {
	if (!img.isNull() && !pPlayer->isStopped())
	{
		ui.label->setAlignment(Qt::AlignCenter);
		ui.label->setPixmap(QPixmap::fromImage(img).scaled(ui.label->size(),
			Qt::KeepAspectRatio, Qt::FastTransformation));
	}
}

void PeopleCountQT::onloadVideoClicked() {
	if (ui.liveCameraFeedCheckBox->isChecked()) {
		ui.liveCameraFeedCheckBox->animateClick();
	}

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

void PeopleCountQT::onLiveCameraFeedPressed(bool bChecked) {
	ui.cameraFeedLabel->setEnabled(bChecked);
	ui.captureNumber->setEnabled(bChecked);

	if (bChecked) {
		onCaptureChange(ui.captureNumber->currentIndex());
	}
	else {
		pPlayer->Stop();
		ui.label->clear();
	}

}

void PeopleCountQT::onCaptureChange(int captureNumber)
{
	if (!pPlayer->loadVideo(captureNumber)) {
		QMessageBox::warning(this, tr("Error"), QString::fromStdString("Could not find camera: " + std::to_string(captureNumber)));
		pPlayer->Stop();
		ui.label->clear();
	}
}

void PeopleCountQT::onPlayPauseButtonClicked()
{
	const QString pause = "Pause";
	const QString play = "Play";

	QString text = ui.playPauseButton->text();
	if (text == pause) {
		ui.playPauseButton->setText(play);
		pPlayer->pause();
	}
	else if (text == play) {
		ui.playPauseButton->setText(pause);
		pPlayer->unpause();
	}
}

void PeopleCountQT::onSaveButtonClicked()
{
	CalibrationSaver calibrationSaver(pCalibrationOptions);
	bool bSuccess = calibrationSaver.saveJson("Calibration/Calibration.json");
	if (bSuccess) {
		QMessageBox::information(this, tr("Saved"), tr("Settings saved successfully"));
	}
	else {
		QMessageBox::warning(this, "Error!", "Could not save settings");
	}
}

/*
 Update UI values and update calibration options incase the setValue is the same as the default value so no event is fired
*/
void PeopleCountQT::connectLoadedCalibrationOptions() {
	QObject::connect(pCalibrationLoader.get(), &CalibrationLoader::contourUpdate, this, [this](int value) {
		this->ui.minArea->setValue(value);

		this->pCalibrationOptions->setupContourConfig(value);
	});

	QObject::connect(pCalibrationLoader.get(), &CalibrationLoader::blobExtractionUpdate, this, [this](int thresholdValue, int openKernelSize, int closeKernelSize) {
		this->ui.thresholdValue->setValue(thresholdValue);
		this->ui.openKernelSize->setValue(openKernelSize);
		this->ui.closeKernelSize->setValue(closeKernelSize);

		this->pCalibrationOptions->setupBlobExtractionConfig(thresholdValue, openKernelSize, closeKernelSize);
	});

	QObject::connect(pCalibrationLoader.get(), &CalibrationLoader::countingLinesUpdate, this, [this](std::string orientation, int outlinePercentage, int inLinePercentage) {
		int index = this->ui.orientation->findText(QString::fromStdString(orientation), Qt::MatchFixedString);

		this->ui.orientation->setCurrentIndex(index);
		this->ui.outLinePercentage->setValue(outlinePercentage);
		this->ui.inLinePercentage->setValue(inLinePercentage);

		this->pCalibrationOptions->setupCountingLinesConfig(orientation, outlinePercentage, inLinePercentage);
	});

	QObject::connect(pCalibrationLoader.get(), &CalibrationLoader::peopleThresholdSizeUpdate, this, [this](int maxArea, int maxWidth, int maxHeight) {
		this->ui.maxWidth->setValue(maxWidth);
		this->ui.maxHeight->setValue(maxHeight);

		this->pCalibrationOptions->setupPeopleThresholdSize(maxArea, maxWidth, maxHeight);
	});
}

void PeopleCountQT::connectCalibrationOptions() {
	QObject::connect(ui.minArea, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getContourConfig()->minArea = value;
	});

	QObject::connect(ui.closeKernelSize, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getBlobExtractionConfg()->morphCloseKernelSize = value;
	});

	QObject::connect(ui.openKernelSize, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getBlobExtractionConfg()->morphOpenKernelSize = value;
	});

	QObject::connect(ui.thresholdValue, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getBlobExtractionConfg()->thresholdValue = value;
	});

	QObject::connect(ui.orientation, &QComboBox::currentTextChanged, this, [this](QString value) {
		std::string orientation = value.toLower().toStdString();
		this->pCalibrationOptions->getCountingLinesConfig()->setOrientationWithString(orientation);
	});

	QObject::connect(ui.inLinePercentage, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getCountingLinesConfig()->inLinePerencateOfScreen = value;
	});

	QObject::connect(ui.outLinePercentage, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getCountingLinesConfig()->outLinePercentageOfScreen = value;
	});

	QObject::connect(ui.maxWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getPeopleThresholdSize()->maxWidth = value;
	});

	QObject::connect(ui.maxHeight, QOverload<int>::of(&QSpinBox::valueChanged), this, [this](int value) {
		this->pCalibrationOptions->getPeopleThresholdSize()->maxHeight = value;
	});

	QObject::connect(ui.imageName, &QComboBox::currentTextChanged, pPlayer.get(), &Player::onImageNameChange);
}


PeopleCountQT::~PeopleCountQT()
{
}
