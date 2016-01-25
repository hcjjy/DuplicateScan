#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QWidget>
class QTabWidget;
class QPushButton;
class ProgressBarContainer;
class QListWidget;
class ReadThread;
class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();
	bool checkoutData(QMap<QString , Qt::CheckState> ,QMap<QString , Qt::CheckState>);
	void run();
	void dirTraverse(QString path);	
protected:
	virtual void resizeEvent(QResizeEvent *event);

private:
	public slots:
	void runPre();
	void canCelRun();

private:
	QTabWidget* m_pTabWidget;
	QPushButton* m_pRun;
	QPushButton* m_pCancel;
	ReadThread *readFile;
	ProgressBarContainer *m_pProgressBarContainer;
};
#endif // MAINWINDOW_H
