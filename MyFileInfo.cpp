#include "MyFileInfo.h"
#include "caculateMD5.h"

#include<QDebug>
MyFileInfo::MyFileInfo(void)
{
	
}

MyFileInfo::MyFileInfo( const QString &file )
	:QFileInfo(file)
{
	
}

MyFileInfo::MyFileInfo( const QFile &file )
	:QFileInfo(file)
{
	
}


MyFileInfo::~MyFileInfo(void)
{
}


void MyFileInfo::setMD5()
{
	MD5 = MD5_file(this->absoluteFilePath().toLocal8Bit().data(),32);
	qDebug()<<MD5<< endl;
}

QString MyFileInfo::getMD5()
{
	return MD5;
}

