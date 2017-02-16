#ifndef MYFILEINFO_H
#define MYFILEINFO_H
#include<QFileInfo>

class MyFileInfo :QFileInfo
{
public:
	MyFileInfo(void);
	MyFileInfo(const QString &file);
	MyFileInfo(const QFile &file);
	void setMD5();
	QString getMD5();
	~MyFileInfo(void);
private:
	QString MD5;
};
#endif // !MYFILEINFO_H

