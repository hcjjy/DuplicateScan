#pragma once
#include<QtGui/QSpinBox>
class MySpinBox :
	public QSpinBox
{
	Q_OBJECT
public:
	MySpinBox(QWidget *parent =NULL);
	virtual ~MySpinBox(void);
signals:
	void valChanged(int val);
protected:
	virtual void keyPressEvent(QKeyEvent *event);
};

