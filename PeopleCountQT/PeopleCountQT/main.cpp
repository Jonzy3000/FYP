#include "PeopleCountQT.h"
#include <QtWidgets/QApplication>
#include <opencv2/opencv.hpp>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	PeopleCountQT w;
	//w.setAttribute(Qt::WA_DeleteOnClose, true);
	w.show();
	return a.exec();
}
