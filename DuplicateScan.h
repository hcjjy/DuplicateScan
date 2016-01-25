#pragma once
#include <QtGui/QWidget>

class QPushButton;
class MyTableView;
class QCheckBox;
class MySpinBox;
class DuplicateScan :
	public QWidget
{
	Q_OBJECT
public:
	DuplicateScan(QWidget *parent = NULL);
	virtual ~DuplicateScan(void);
	void clearItem();
protected:
	virtual void resizeEvent(QResizeEvent *event);
signals:
	void conditionsChanged(int state,int value);
public slots:
	void threadFinished();
	void stateChanged(int state);
	void valChanged(int value);
private:
	
	QPushButton *m_pDeleteCheckedFiles;
	QPushButton *m_pMoveCheckedFiles;
	MySpinBox *m_pMinFileSize;
	QCheckBox *m_pScreenFileSize;

	QPushButton *m_pLoadResult;
	MyTableView *m_pScanResult;
};

