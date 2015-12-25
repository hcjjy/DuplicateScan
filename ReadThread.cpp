#include "ReadThread.h"
#include "mainwindow.h"

ReadThread::ReadThread( QWidget *parent /*= NULL*/ )
{
	
}


ReadThread::~ReadThread(void)
{
}

void ReadThread::run()
{
	m_pMainThread->run();
}

void ReadThread::RevPtr( MainWindow* mainThread )
{
	m_pMainThread = mainThread;
}
