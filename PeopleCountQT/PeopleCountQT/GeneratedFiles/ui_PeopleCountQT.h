/********************************************************************************
** Form generated from reading UI file 'PeopleCountQT.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PEOPLECOUNTQT_H
#define UI_PEOPLECOUNTQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PeopleCountQTClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QPushButton *playPauseButton;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *saveButton;
    QPushButton *loadVideo;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout_8;
    QLabel *label_5;
    QLineEdit *roomName;
    QLabel *label_6;
    QSpinBox *maxOccupancy;
    QGroupBox *groupBox;
    QFormLayout *formLayout_7;
    QLabel *cameraFeedLabel;
    QComboBox *captureNumber;
    QLabel *label_4;
    QCheckBox *liveCameraFeedCheckBox;
    QGroupBox *groupBox_19;
    QFormLayout *formLayout_6;
    QLabel *label_2;
    QComboBox *imageName;
    QGroupBox *groupBox_14;
    QFormLayout *formLayout;
    QLabel *label_24;
    QSpinBox *minArea;
    QGroupBox *groupBox_15;
    QFormLayout *formLayout_2;
    QLabel *label_25;
    QLabel *label_26;
    QLabel *label_27;
    QSpinBox *closeKernelSize;
    QSpinBox *openKernelSize;
    QSpinBox *thresholdValue;
    QGroupBox *groupBox_16;
    QFormLayout *formLayout_3;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QComboBox *orientation;
    QSpinBox *inLinePercentage;
    QSpinBox *outLinePercentage;
    QGroupBox *groupBox_17;
    QFormLayout *formLayout_4;
    QLabel *label_31;
    QSpinBox *maxWidth;
    QLabel *label_32;
    QSpinBox *maxHeight;
    QGroupBox *groupBox_18;
    QGridLayout *gridLayout;
    QLabel *label_33;
    QLabel *label_34;
    QSpinBox *portNumber;
    QLineEdit *ipAddress;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *PeopleCountQTClass)
    {
        if (PeopleCountQTClass->objectName().isEmpty())
            PeopleCountQTClass->setObjectName(QStringLiteral("PeopleCountQTClass"));
        PeopleCountQTClass->resize(1314, 855);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(PeopleCountQTClass->sizePolicy().hasHeightForWidth());
        PeopleCountQTClass->setSizePolicy(sizePolicy);
        PeopleCountQTClass->setToolButtonStyle(Qt::ToolButtonTextOnly);
        PeopleCountQTClass->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(PeopleCountQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(15);
        playPauseButton = new QPushButton(centralWidget);
        playPauseButton->setObjectName(QStringLiteral("playPauseButton"));

        gridLayout_2->addWidget(playPauseButton, 6, 0, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(720, 480));
        label->setStyleSheet(QStringLiteral("Background-color: #000;"));

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        saveButton = new QPushButton(centralWidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));

        horizontalLayout->addWidget(saveButton);

        loadVideo = new QPushButton(centralWidget);
        loadVideo->setObjectName(QStringLiteral("loadVideo"));

        horizontalLayout->addWidget(loadVideo);


        gridLayout_2->addLayout(horizontalLayout, 5, 1, 2, 1);

        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy3);
        scrollArea->setMinimumSize(QSize(300, 550));
        scrollArea->setMaximumSize(QSize(350, 16777215));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 281, 779));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        groupBox_13 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setFlat(true);
        groupBox_13->setCheckable(false);
        verticalLayout_4 = new QVBoxLayout(groupBox_13);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(-1, -1, 2, -1);
        groupBox_2 = new QGroupBox(groupBox_13);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setFlat(false);
        groupBox_2->setCheckable(false);
        formLayout_8 = new QFormLayout(groupBox_2);
        formLayout_8->setSpacing(6);
        formLayout_8->setContentsMargins(11, 11, 11, 11);
        formLayout_8->setObjectName(QStringLiteral("formLayout_8"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout_8->setWidget(0, QFormLayout::LabelRole, label_5);

        roomName = new QLineEdit(groupBox_2);
        roomName->setObjectName(QStringLiteral("roomName"));

        formLayout_8->setWidget(0, QFormLayout::FieldRole, roomName);

        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        formLayout_8->setWidget(1, QFormLayout::LabelRole, label_6);

        maxOccupancy = new QSpinBox(groupBox_2);
        maxOccupancy->setObjectName(QStringLiteral("maxOccupancy"));
        maxOccupancy->setMaximum(1000);

        formLayout_8->setWidget(1, QFormLayout::FieldRole, maxOccupancy);


        verticalLayout_4->addWidget(groupBox_2);

        groupBox = new QGroupBox(groupBox_13);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        formLayout_7 = new QFormLayout(groupBox);
        formLayout_7->setSpacing(6);
        formLayout_7->setContentsMargins(11, 11, 11, 11);
        formLayout_7->setObjectName(QStringLiteral("formLayout_7"));
        cameraFeedLabel = new QLabel(groupBox);
        cameraFeedLabel->setObjectName(QStringLiteral("cameraFeedLabel"));
        cameraFeedLabel->setEnabled(false);

        formLayout_7->setWidget(2, QFormLayout::LabelRole, cameraFeedLabel);

        captureNumber = new QComboBox(groupBox);
        captureNumber->setObjectName(QStringLiteral("captureNumber"));
        captureNumber->setEnabled(false);

        formLayout_7->setWidget(2, QFormLayout::FieldRole, captureNumber);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout_7->setWidget(1, QFormLayout::LabelRole, label_4);

        liveCameraFeedCheckBox = new QCheckBox(groupBox);
        liveCameraFeedCheckBox->setObjectName(QStringLiteral("liveCameraFeedCheckBox"));

        formLayout_7->setWidget(1, QFormLayout::FieldRole, liveCameraFeedCheckBox);


        verticalLayout_4->addWidget(groupBox);

        groupBox_19 = new QGroupBox(groupBox_13);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        formLayout_6 = new QFormLayout(groupBox_19);
        formLayout_6->setSpacing(6);
        formLayout_6->setContentsMargins(11, 11, 11, 11);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        label_2 = new QLabel(groupBox_19);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_2);

        imageName = new QComboBox(groupBox_19);
        imageName->setObjectName(QStringLiteral("imageName"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, imageName);


        verticalLayout_4->addWidget(groupBox_19);

        groupBox_14 = new QGroupBox(groupBox_13);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        formLayout = new QFormLayout(groupBox_14);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_24 = new QLabel(groupBox_14);
        label_24->setObjectName(QStringLiteral("label_24"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_24);

        minArea = new QSpinBox(groupBox_14);
        minArea->setObjectName(QStringLiteral("minArea"));
        minArea->setMaximum(1000);
        minArea->setValue(0);

        formLayout->setWidget(1, QFormLayout::FieldRole, minArea);


        verticalLayout_4->addWidget(groupBox_14);

        groupBox_15 = new QGroupBox(groupBox_13);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        formLayout_2 = new QFormLayout(groupBox_15);
        formLayout_2->setSpacing(6);
        formLayout_2->setContentsMargins(11, 11, 11, 11);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        label_25 = new QLabel(groupBox_15);
        label_25->setObjectName(QStringLiteral("label_25"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_25);

        label_26 = new QLabel(groupBox_15);
        label_26->setObjectName(QStringLiteral("label_26"));

        formLayout_2->setWidget(3, QFormLayout::LabelRole, label_26);

        label_27 = new QLabel(groupBox_15);
        label_27->setObjectName(QStringLiteral("label_27"));

        formLayout_2->setWidget(5, QFormLayout::LabelRole, label_27);

        closeKernelSize = new QSpinBox(groupBox_15);
        closeKernelSize->setObjectName(QStringLiteral("closeKernelSize"));
        closeKernelSize->setMaximum(30);
        closeKernelSize->setValue(0);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, closeKernelSize);

        openKernelSize = new QSpinBox(groupBox_15);
        openKernelSize->setObjectName(QStringLiteral("openKernelSize"));
        openKernelSize->setMaximum(30);
        openKernelSize->setValue(0);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, openKernelSize);

        thresholdValue = new QSpinBox(groupBox_15);
        thresholdValue->setObjectName(QStringLiteral("thresholdValue"));
        thresholdValue->setMaximum(255);
        thresholdValue->setValue(0);

        formLayout_2->setWidget(5, QFormLayout::FieldRole, thresholdValue);


        verticalLayout_4->addWidget(groupBox_15);

        groupBox_16 = new QGroupBox(groupBox_13);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        formLayout_3 = new QFormLayout(groupBox_16);
        formLayout_3->setSpacing(6);
        formLayout_3->setContentsMargins(11, 11, 11, 11);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        label_28 = new QLabel(groupBox_16);
        label_28->setObjectName(QStringLiteral("label_28"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_28);

        label_29 = new QLabel(groupBox_16);
        label_29->setObjectName(QStringLiteral("label_29"));

        formLayout_3->setWidget(3, QFormLayout::LabelRole, label_29);

        label_30 = new QLabel(groupBox_16);
        label_30->setObjectName(QStringLiteral("label_30"));

        formLayout_3->setWidget(5, QFormLayout::LabelRole, label_30);

        orientation = new QComboBox(groupBox_16);
        orientation->setObjectName(QStringLiteral("orientation"));

        formLayout_3->setWidget(0, QFormLayout::FieldRole, orientation);

        inLinePercentage = new QSpinBox(groupBox_16);
        inLinePercentage->setObjectName(QStringLiteral("inLinePercentage"));
        inLinePercentage->setMaximum(100);
        inLinePercentage->setValue(0);

        formLayout_3->setWidget(3, QFormLayout::FieldRole, inLinePercentage);

        outLinePercentage = new QSpinBox(groupBox_16);
        outLinePercentage->setObjectName(QStringLiteral("outLinePercentage"));
        outLinePercentage->setMaximum(100);
        outLinePercentage->setValue(0);

        formLayout_3->setWidget(5, QFormLayout::FieldRole, outLinePercentage);


        verticalLayout_4->addWidget(groupBox_16);

        groupBox_17 = new QGroupBox(groupBox_13);
        groupBox_17->setObjectName(QStringLiteral("groupBox_17"));
        sizePolicy2.setHeightForWidth(groupBox_17->sizePolicy().hasHeightForWidth());
        groupBox_17->setSizePolicy(sizePolicy2);
        formLayout_4 = new QFormLayout(groupBox_17);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_31 = new QLabel(groupBox_17);
        label_31->setObjectName(QStringLiteral("label_31"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_31);

        maxWidth = new QSpinBox(groupBox_17);
        maxWidth->setObjectName(QStringLiteral("maxWidth"));
        maxWidth->setMaximum(500);
        maxWidth->setValue(0);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, maxWidth);

        label_32 = new QLabel(groupBox_17);
        label_32->setObjectName(QStringLiteral("label_32"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_32);

        maxHeight = new QSpinBox(groupBox_17);
        maxHeight->setObjectName(QStringLiteral("maxHeight"));
        maxHeight->setMaximum(500);
        maxHeight->setValue(0);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, maxHeight);


        verticalLayout_4->addWidget(groupBox_17);

        groupBox_18 = new QGroupBox(groupBox_13);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(groupBox_18->sizePolicy().hasHeightForWidth());
        groupBox_18->setSizePolicy(sizePolicy4);
        groupBox_18->setMaximumSize(QSize(160000, 16777215));
        gridLayout = new QGridLayout(groupBox_18);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setHorizontalSpacing(2);
        gridLayout->setContentsMargins(-1, -1, 5, -1);
        label_33 = new QLabel(groupBox_18);
        label_33->setObjectName(QStringLiteral("label_33"));

        gridLayout->addWidget(label_33, 1, 0, 1, 1);

        label_34 = new QLabel(groupBox_18);
        label_34->setObjectName(QStringLiteral("label_34"));

        gridLayout->addWidget(label_34, 4, 0, 1, 1);

        portNumber = new QSpinBox(groupBox_18);
        portNumber->setObjectName(QStringLiteral("portNumber"));
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(portNumber->sizePolicy().hasHeightForWidth());
        portNumber->setSizePolicy(sizePolicy5);
        portNumber->setMaximum(65536);
        portNumber->setValue(0);

        gridLayout->addWidget(portNumber, 4, 1, 1, 2);

        ipAddress = new QLineEdit(groupBox_18);
        ipAddress->setObjectName(QStringLiteral("ipAddress"));

        gridLayout->addWidget(ipAddress, 1, 1, 1, 1);


        verticalLayout_4->addWidget(groupBox_18);


        verticalLayout_3->addWidget(groupBox_13);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        gridLayout_2->addWidget(scrollArea, 3, 1, 1, 1);

        PeopleCountQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PeopleCountQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1314, 21));
        PeopleCountQTClass->setMenuBar(menuBar);

        retranslateUi(PeopleCountQTClass);

        QMetaObject::connectSlotsByName(PeopleCountQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *PeopleCountQTClass)
    {
        PeopleCountQTClass->setWindowTitle(QApplication::translate("PeopleCountQTClass", "PeopleCountQT", Q_NULLPTR));
        playPauseButton->setText(QApplication::translate("PeopleCountQTClass", "Pause", Q_NULLPTR));
        label->setText(QString());
        saveButton->setText(QApplication::translate("PeopleCountQTClass", "Save Settings", Q_NULLPTR));
        loadVideo->setText(QApplication::translate("PeopleCountQTClass", "Load Video", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("PeopleCountQTClass", "Calibration", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("PeopleCountQTClass", "Room Details", Q_NULLPTR));
        label_5->setText(QApplication::translate("PeopleCountQTClass", "Room Name", Q_NULLPTR));
        label_6->setText(QApplication::translate("PeopleCountQTClass", "Room Size", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("PeopleCountQTClass", "Live", Q_NULLPTR));
        cameraFeedLabel->setText(QApplication::translate("PeopleCountQTClass", "Camera Feed Slot", Q_NULLPTR));
        captureNumber->clear();
        captureNumber->insertItems(0, QStringList()
         << QApplication::translate("PeopleCountQTClass", "0", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "1", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "2", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "3", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "4", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "5", Q_NULLPTR)
        );
        label_4->setText(QApplication::translate("PeopleCountQTClass", "Use Live Camera Feed", Q_NULLPTR));
        liveCameraFeedCheckBox->setText(QString());
        groupBox_19->setTitle(QApplication::translate("PeopleCountQTClass", "Show Image", Q_NULLPTR));
        label_2->setText(QApplication::translate("PeopleCountQTClass", "Image Name", Q_NULLPTR));
        imageName->clear();
        imageName->insertItems(0, QStringList()
         << QApplication::translate("PeopleCountQTClass", "Output", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "Threshold", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "Background Subtraction", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "Morph Open", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "Morph Close", Q_NULLPTR)
        );
        groupBox_14->setTitle(QApplication::translate("PeopleCountQTClass", "Contours", Q_NULLPTR));
        label_24->setText(QApplication::translate("PeopleCountQTClass", "Minimum Area", Q_NULLPTR));
        groupBox_15->setTitle(QApplication::translate("PeopleCountQTClass", "Blob Extraction", Q_NULLPTR));
        label_25->setText(QApplication::translate("PeopleCountQTClass", "Close Kernel Size", Q_NULLPTR));
        label_26->setText(QApplication::translate("PeopleCountQTClass", "Open Kernel Size", Q_NULLPTR));
        label_27->setText(QApplication::translate("PeopleCountQTClass", "Threshold Value", Q_NULLPTR));
        groupBox_16->setTitle(QApplication::translate("PeopleCountQTClass", "Counting Lines", Q_NULLPTR));
        label_28->setText(QApplication::translate("PeopleCountQTClass", "Orientation", Q_NULLPTR));
        label_29->setText(QApplication::translate("PeopleCountQTClass", "In Line Placement (%)", Q_NULLPTR));
        label_30->setText(QApplication::translate("PeopleCountQTClass", "Out Line Placement (%)", Q_NULLPTR));
        orientation->clear();
        orientation->insertItems(0, QStringList()
         << QApplication::translate("PeopleCountQTClass", "Vertical", Q_NULLPTR)
         << QApplication::translate("PeopleCountQTClass", "Horizontal", Q_NULLPTR)
        );
        orientation->setCurrentText(QApplication::translate("PeopleCountQTClass", "Vertical", Q_NULLPTR));
        groupBox_17->setTitle(QApplication::translate("PeopleCountQTClass", "People Threshold Size", Q_NULLPTR));
        label_31->setText(QApplication::translate("PeopleCountQTClass", "Max Width (px)", Q_NULLPTR));
        label_32->setText(QApplication::translate("PeopleCountQTClass", "Max Height (px)", Q_NULLPTR));
        groupBox_18->setTitle(QApplication::translate("PeopleCountQTClass", "Server Settings", Q_NULLPTR));
        label_33->setText(QApplication::translate("PeopleCountQTClass", "IP Address       ", Q_NULLPTR));
        label_34->setText(QApplication::translate("PeopleCountQTClass", "Port", Q_NULLPTR));
        ipAddress->setInputMask(QString());
        ipAddress->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class PeopleCountQTClass: public Ui_PeopleCountQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEOPLECOUNTQT_H
