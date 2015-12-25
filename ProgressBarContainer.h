#pragma once
#include<QtGui/QFrame>
class QLabel;
class RunProgressBar;
class ProgressBarContainer :
	public QFrame
{
public:
	ProgressBarContainer(QWidget *parent = NULL);
	~ProgressBarContainer(void);
protected:
	virtual void resizeEvent(QResizeEvent *event);
private:
	QLabel * m_pProgressBarStatus;
	RunProgressBar *m_pRunProgressBar;
};

