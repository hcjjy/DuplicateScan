#include "SimpleMatchConditions.h"
#include <QtGui>
SimpleMatchConditions::SimpleMatchConditions( QWidget * parent /*= NULL*/ )
	:QFrame(parent)
{
	this->setFrameStyle(QFrame::WinPanel|QFrame::Raised);
	
	m_pTitleLabel = new QLabel(tr("choose your conditons of same file"),this);
	m_pNamesIdentical = new QCheckBox(tr("names are identical"),this);
	m_pSizesIdentical = new QCheckBox(tr("sizes are identical"),this);
	m_pMD5Identical = new QCheckBox(tr("MD5 are identical"),this);
}


SimpleMatchConditions::~SimpleMatchConditions(void)
{

}

void SimpleMatchConditions::resizeEvent( QResizeEvent* event )
{
	m_pTitleLabel->setGeometry(30,30,150,30);
	m_pNamesIdentical->setGeometry(30,50,150,30);
	m_pSizesIdentical->setGeometry(30,70,150,30);
	m_pMD5Identical->setGeometry(30,90,150,30);
}

QMap<QString , Qt::CheckState> SimpleMatchConditions::getConditionsMap()
{
	QMap<QString ,Qt::CheckState> conditonsState;
	conditonsState[tr("names")] = m_pNamesIdentical->checkState();
	conditonsState[tr("sizes")] = m_pSizesIdentical->checkState();
	conditonsState[tr("MD5")] = m_pMD5Identical->checkState();
	return conditonsState;
}
