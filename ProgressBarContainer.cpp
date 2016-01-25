#include "ProgressBarContainer.h"
#include "RunProgressBar.h"
#include <QtGui>

ProgressBarContainer::ProgressBarContainer( QWidget *parent /*= NULL*/ )
	:QFrame(parent)
{
	this->setFrameStyle(QFrame::WinPanel|QFrame::Raised);

	m_pProgressBarStatus = new QLabel("Status:Idle",this);
	m_pRunProgressBar = new RunProgressBar(this);

}


ProgressBarContainer::~ProgressBarContainer(void)
{
}

void ProgressBarContainer::resizeEvent( QResizeEvent *event )
{
	m_pProgressBarStatus->setGeometry(40,10,70,20);
	m_pRunProgressBar->setGeometry(40,100,500,10);
}
