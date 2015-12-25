#include "DuplicateScan.h"
#include "MyTableView.h"
#include <QtGui>
//定义widget 背景颜色值
#define WIDGET_BACKCOLOR QColor(240, 240, 240)


//这里pWidget传QWidget指针
#define SET_WIDGET_BACKCOLOR(pWidget)		do {						\
	pWidget->setAutoFillBackground(true);									\
	QPalette paletter;														\
	paletter.setColor(QPalette::Background, WIDGET_BACKCOLOR);			\
	pWidget->setPalette(paletter);																	\
}while(0)
DuplicateScan::DuplicateScan( QWidget *parent /*= NULL*/ )
	:QWidget(parent)
{
	SET_WIDGET_BACKCOLOR(this);
	
	m_pDeleteCheckedFiles  = new QPushButton(tr("&Delete checked files"),this);
	m_pMoveCheckedFiles  = new QPushButton(tr("&Move checked files..."),this);

	m_pScanResult = new MyTableView(this);

	connect(m_pDeleteCheckedFiles,SIGNAL(clicked()),m_pScanResult,SLOT(deleteSelectedItem()));
	connect(m_pMoveCheckedFiles,SIGNAL(clicked()),m_pScanResult,SLOT(takeSelectedItem()));
	
}


DuplicateScan::~DuplicateScan(void)
{

}

void DuplicateScan::resizeEvent( QResizeEvent *event )
{

	m_pDeleteCheckedFiles->setGeometry(20,240,140,25);
	m_pMoveCheckedFiles->setGeometry(20,300,140,25);

	m_pScanResult->setGeometry(200,30,width()-200,300);

	
}

void DuplicateScan::screenItem()
{
	m_pScanResult->screenItem();
}

void DuplicateScan::clearItem()
{
	m_pScanResult->clearItem();

}

void DuplicateScan::clearModel()
{
	m_pScanResult->clearModel();
}

void DuplicateScan::threadFinished()
{
	m_pScanResult->threadFinished();
}


