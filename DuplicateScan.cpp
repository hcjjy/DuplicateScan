#include "DuplicateScan.h"
#include "MyTableView.h"
#include "MySpinBox.h"
#include <QtGui>

DuplicateScan::DuplicateScan( QWidget *parent /*= NULL*/ )
	:QWidget(parent)
{
	setAutoFillBackground(true);

	m_pDeleteCheckedFiles  = new QPushButton(tr("&Delete checked files"),this);
	m_pMoveCheckedFiles  = new QPushButton(tr("&Move checked files..."),this);
	m_pMinFileSize = new MySpinBox(this);

	m_pScreenFileSize = new QCheckBox(tr("set MinSize"),this);
	m_pMinFileSize->setRange(0,INT_MAX);
	
	m_pLoadResult = new QPushButton(tr("LoadResult"),this);
	m_pScanResult = new MyTableView(this);

	connect(m_pDeleteCheckedFiles,SIGNAL(clicked()),m_pScanResult,SLOT(deleteSelectedItem()));
	connect(m_pMoveCheckedFiles,SIGNAL(clicked()),m_pScanResult,SLOT(takeSelectedItem()));

	connect(m_pLoadResult,SIGNAL(clicked()),m_pScanResult,SLOT(loadResult()));

	connect(m_pMinFileSize,SIGNAL(valChanged(int )),this,SLOT(valChanged(int )));
	connect(m_pScreenFileSize,SIGNAL(stateChanged(int)),this,SLOT(stateChanged(int)));

	connect(this,SIGNAL(conditionsChanged(int,int)),m_pScanResult,SLOT(screenFileSize(int,int)));

	
	
}


DuplicateScan::~DuplicateScan(void)
{

}

void DuplicateScan::resizeEvent( QResizeEvent *event )
{
	m_pMinFileSize->setGeometry(20,100,140,25);
	m_pScreenFileSize->setGeometry(30,140,140,25);

	m_pDeleteCheckedFiles->setGeometry(20,240,140,25);
	m_pMoveCheckedFiles->setGeometry(20,300,140,25);

	m_pLoadResult->setGeometry(20,190,140,25);
	m_pScanResult->setGeometry(200,30,width()-200,300);

	
}


void DuplicateScan::clearItem()
{
	m_pScanResult->clearItem();
}

void DuplicateScan::threadFinished()
{
	m_pScanResult->threadFinished();
}

void DuplicateScan::stateChanged(int state)
{
	emit conditionsChanged(state,m_pMinFileSize->value());
}

void DuplicateScan::valChanged(int value)
{
	emit conditionsChanged(m_pScreenFileSize->checkState(),value);
}


