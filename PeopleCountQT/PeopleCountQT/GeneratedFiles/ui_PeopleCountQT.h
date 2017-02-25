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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PeopleCountQTClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *loadVideo;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *PeopleCountQTClass)
    {
        if (PeopleCountQTClass->objectName().isEmpty())
            PeopleCountQTClass->setObjectName(QStringLiteral("PeopleCountQTClass"));
        PeopleCountQTClass->resize(1101, 614);
        centralWidget = new QWidget(PeopleCountQTClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral("background-color: rgb(255, 170, 255);"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 30, 720, 480));
        label->setStyleSheet(QStringLiteral("Background-color: #000;"));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(810, 0, 291, 561));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        loadVideo = new QPushButton(gridLayoutWidget);
        loadVideo->setObjectName(QStringLiteral("loadVideo"));

        gridLayout->addWidget(loadVideo, 0, 0, 1, 1);

        PeopleCountQTClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(PeopleCountQTClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1101, 21));
        PeopleCountQTClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(PeopleCountQTClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        PeopleCountQTClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(PeopleCountQTClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        PeopleCountQTClass->setStatusBar(statusBar);

        retranslateUi(PeopleCountQTClass);

        QMetaObject::connectSlotsByName(PeopleCountQTClass);
    } // setupUi

    void retranslateUi(QMainWindow *PeopleCountQTClass)
    {
        PeopleCountQTClass->setWindowTitle(QApplication::translate("PeopleCountQTClass", "PeopleCountQT", Q_NULLPTR));
        label->setText(QString());
        loadVideo->setText(QApplication::translate("PeopleCountQTClass", "Load Video", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class PeopleCountQTClass: public Ui_PeopleCountQTClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PEOPLECOUNTQT_H
