#pragma once
#include <QThread>
class MainWindow;
class ReadThread :
	public QThread
{
	Q_OBJECT
public:
	ReadThread(QWidget *parent = NULL);
	virtual ~ReadThread(void);
	void RevPtr(MainWindow* mainThread);
protected:
	void run();
private:
	MainWindow* m_pMainThread;
};

