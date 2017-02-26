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
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_4;
    QGroupBox *groupBox_19;
    QFormLayout *formLayout_6;
    QLabel *label_35;
    QComboBox *comboBox_3;
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
    QLabel *label_32;
    QSpinBox *maxWidth;
    QSpinBox *maxHeight;
    QGroupBox *groupBox_18;
    QFormLayout *formLayout_5;
    QLabel *label_33;
    QLabel *label_34;
    QLineEdit *ipAddress;
    QSpinBox *portNumber;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *loadVideo;
    QMenuBar *menuBar;

    void setupUi(QMainWindow *PeopleCountQTClass)
    {
        if (PeopleCountQTClass->objectName().isEmpty())
            PeopleCountQTClass->setObjectName(QStringLiteral("PeopleCountQTClass"));
        PeopleCountQTClass->resize(1154, 630);
        PeopleCountQTClass->setToolButtonStyle(Qt::ToolButtonTextOnly);
        PeopleCountQTClass->setTabShape(QTabWidget::Rounded);
        centralWidget = new QWidget(PeopleCountQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setHorizontalSpacing(15);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy1);
        scrollArea->setMinimumSize(QSize(300, 550));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName(QStringLiteral("scrollAreaWidgetContents_3"));
        scrollAreaWidgetContents_3->setGeometry(QRect(0, -73, 281, 621));
        verticalLayout_3 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox_13 = new QGroupBox(scrollAreaWidgetContents_3);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        verticalLayout_4 = new QVBoxLayout(groupBox_13);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        groupBox_19 = new QGroupBox(groupBox_13);
        groupBox_19->setObjectName(QStringLiteral("groupBox_19"));
        formLayout_6 = new QFormLayout(groupBox_19);
        formLayout_6->setSpacing(6);
        formLayout_6->setContentsMargins(11, 11, 11, 11);
        formLayout_6->setObjectName(QStringLiteral("formLayout_6"));
        label_35 = new QLabel(groupBox_19);
        label_35->setObjectName(QStringLiteral("label_35"));

        formLayout_6->setWidget(0, QFormLayout::LabelRole, label_35);

        comboBox_3 = new QComboBox(groupBox_19);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        formLayout_6->setWidget(0, QFormLayout::FieldRole, comboBox_3);


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
        QSizePolicy sizePolicy2(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_17->sizePolicy().hasHeightForWidth());
        groupBox_17->setSizePolicy(sizePolicy2);
        formLayout_4 = new QFormLayout(groupBox_17);
        formLayout_4->setSpacing(6);
        formLayout_4->setContentsMargins(11, 11, 11, 11);
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        label_31 = new QLabel(groupBox_17);
        label_31->setObjectName(QStringLiteral("label_31"));

        formLayout_4->setWidget(1, QFormLayout::LabelRole, label_31);

        label_32 = new QLabel(groupBox_17);
        label_32->setObjectName(QStringLiteral("label_32"));

        formLayout_4->setWidget(3, QFormLayout::LabelRole, label_32);

        maxWidth = new QSpinBox(groupBox_17);
        maxWidth->setObjectName(QStringLiteral("maxWidth"));
        maxWidth->setMaximum(500);
        maxWidth->setValue(0);

        formLayout_4->setWidget(1, QFormLayout::FieldRole, maxWidth);

        maxHeight = new QSpinBox(groupBox_17);
        maxHeight->setObjectName(QStringLiteral("maxHeight"));
        maxHeight->setMaximum(500);
        maxHeight->setValue(0);

        formLayout_4->setWidget(3, QFormLayout::FieldRole, maxHeight);


        verticalLayout_4->addWidget(groupBox_17);

        groupBox_18 = new QGroupBox(groupBox_13);
        groupBox_18->setObjectName(QStringLiteral("groupBox_18"));
        formLayout_5 = new QFormLayout(groupBox_18);
        formLayout_5->setSpacing(6);
        formLayout_5->setContentsMargins(11, 11, 11, 11);
        formLayout_5->setObjectName(QStringLiteral("formLayout_5"));
        label_33 = new QLabel(groupBox_18);
        label_33->setObjectName(QStringLiteral("label_33"));

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_33);

        label_34 = new QLabel(groupBox_18);
        label_34->setObjectName(QStringLiteral("label_34"));

        formLayout_5->setWidget(3, QFormLayout::LabelRole, label_34);

        ipAddress = new QLineEdit(groupBox_18);
        ipAddress->setObjectName(QStringLiteral("ipAddress"));

        formLayout_5->setWidget(1, QFormLayout::FieldRole, ipAddress);

        portNumber = new QSpinBox(groupBox_18);
        portNumber->setObjectName(QStringLiteral("portNumber"));
        portNumber->setMaximum(65536);
        portNumber->setValue(0);

        formLayout_5->setWidget(3, QFormLayout::FieldRole, portNumber);


        verticalLayout_4->addWidget(groupBox_18);


        verticalLayout_3->addWidget(groupBox_13);

        scrollArea->setWidget(scrollAreaWidgetContents_3);

        gridLayout_2->addWidget(scrollArea, 3, 1, 1, 1);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy2.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy2);
        label->setMinimumSize(QSize(720, 480));
        label->setStyleSheet(QStringLiteral("Background-color: #000;"));

        gridLayout_2->addWidget(label, 3, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        loadVideo = new QPushButton(centralWidget);
        loadVideo->setObjectName(QStringLiteral("loadVideo"));

        horizontalLayout->addWidget(loadVideo);


        gridLayout_2->addLayout(horizontalLayout, 5, 1, 2, 1);

        PeopleCountQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PeopleCountQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1154, 21));
        PeopleCountQTClass->setMenuBar(menuBar);

        retranslateUi(PeopleCountQTClass);

        QMetaObject::connectSlotsByName(PeopleCountQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *PeopleCountQTClass)
    {
        PeopleCountQTClass->setWindowTitle(QApplication::translate("PeopleCountQTClass", "PeopleCountQT", Q_NULLPTR));
        groupBox_13->setTitle(QApplication::translate("PeopleCountQTClass", "Calibration", Q_NULLPTR));
        groupBox_19->setTitle(QApplication::translate("PeopleCountQTClass", "Show Image", Q_NULLPTR));
        label_35->setText(QApplication::translate("PeopleCountQTClass", "Image Name", Q_NULLPTR));
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
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
        label_33->setText(QApplication::translate("PeopleCountQTClass", "IP Address", Q_NULLPTR));
        label_34->setText(QApplication::translate("PeopleCountQTClass", "Port", Q_NULLPTR));
        ipAddress->setInputMask(QApplication::translate("PeopleCountQTClass", "000.000.000.000;_", Q_NULLPTR));
        label->setText(QString());
        pushButton->setText(QApplication::translate("PeopleCountQTClass", "Save", Q_NULLPTR));
        loadVideo->setText(QApplication::translate("PeopleCountQTClass", "Load Video", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PeopleCountQTClass: public Ui_PeopleCountQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEOPLECOUNTQT_H
