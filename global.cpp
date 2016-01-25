#include "global.h"

QMap<QString, QList<TableData> >fileInfoMap;

bool stopflag;

QDataStream& operator<<(QDataStream& out ,TableData tData)
{
	out<<tData.fileName
	   <<tData.filePath
	   <<tData.fileSize
	   <<tData.fileTime
	   <<tData.fileMD5;
	return out;
}

QDataStream& operator>>( QDataStream& in,TableData &tData )
{
	in>>tData.fileName
	  >>tData.filePath
	  >>tData.fileSize
	  >>tData.fileTime
	  >>tData.fileMD5;
	return in;
}
