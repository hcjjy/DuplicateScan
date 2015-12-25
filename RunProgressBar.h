#pragma once
#include <QtGui/QProgressBar>
class QLabel;
class RunProgressBar :
	public QProgressBar
{
public:
	RunProgressBar(QWidget *parent = NULL);
	virtual ~RunProgressBar(void);
private:
	QLabel *m_pProgressStatus;
};

