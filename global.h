#ifndef GLOBAL_H
#define GLOBAL_H
#include <QtGui>
#include <iostream>
using namespace std;

struct TableData
{
	QString fileName;
	QString filePath;
	qint64 fileSize;
	QDateTime fileTime;
	QString fileMD5;
};

extern bool stopflag;
extern QMap<QString, QList<TableData> >fileInfoMap;
QDataStream& operator <<(QDataStream& out,TableData tData);
QDataStream& operator >>(QDataStream& in,TableData &tData);

#endif