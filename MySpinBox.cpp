#include "MySpinBox.h"
#include <QtGui>

MySpinBox::MySpinBox( QWidget *parent /*=NULL*/ )
	:QSpinBox(parent)
{
	setValue(0);
}


MySpinBox::~MySpinBox(void)
{
}

void MySpinBox::keyPressEvent( QKeyEvent *event )
{
	static int oldValue =0;
	int key = event->key();
	switch(event->key())
	{
	case Qt::Key_Return:
	case Qt::Key_Enter:
		QSpinBox::keyPressEvent(event);
		if (oldValue != value())
		{
			emit valChanged(value());
			oldValue = value();
		}
		break;
	default:
		QSpinBox::keyPressEvent(event);
	}
}
