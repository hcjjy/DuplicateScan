#include "mainwindow.h"
#include <QtGui/QApplication>
#include <QTextCodec>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	MainWindow w;
	w.show();
	return a.exec();
}
