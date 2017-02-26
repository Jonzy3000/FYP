#include "PeopleCountQT.h"
#include <QtWidgets/QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PeopleCountQT w;
	w.show();
	return a.exec();
}


/*
We need a class to load json, class to save json and class to link up values to algorithm

*/

