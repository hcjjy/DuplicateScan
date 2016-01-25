#include "OptionsSetting.h"
#include "SimpleMatchConditions.h"
#include "FileDirList.h"
#include <QtGui>

OptionsSetting::OptionsSetting( QWidget *parent /*= NULL*/ )
	:QWidget(parent)
{
	setAutoFillBackground(true);

	m_pConditions = new SimpleMatchConditions(this);
	m_pFileDirList = new FileDirList(this);
}


OptionsSetting::~OptionsSetting(void)
{
}

void OptionsSetting::resizeEvent( QResizeEvent *event )
{
	m_pConditions->setGeometry(20,20,300,180);
	m_pFileDirList->setGeometry(20,220,300,180);
}

QMap<QString,Qt::CheckState> OptionsSetting::getFileDirMap()
{
	return m_pFileDirList->getFileDirMap();
}

QMap<QString , Qt::CheckState> OptionsSetting::getConditionsMap()
{
	return m_pConditions->getConditionsMap();
}


