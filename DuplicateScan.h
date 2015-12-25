#pragma once
#include <QtGui/QWidget>
#include <QMultiMap>
#include <QFileInfo>
class QPushButton;
class QSplitter;
class MyTableView;
class DuplicateScan :
	public QWidget
{
	Q_OBJECT
public:
	DuplicateScan(QWidget *parent = NULL);
	virtual ~DuplicateScan(void);
	void screenItem();
	void clearItem();
	void clearModel();
protected:
	virtual void resizeEvent(QResizeEvent *event);
public slots:
	void threadFinished();
private:
	

	
	QPushButton *m_pDeleteCheckedFiles;
	QPushButton *m_pMoveCheckedFiles;

	MyTableView *m_pScanResult;

	
	
};

