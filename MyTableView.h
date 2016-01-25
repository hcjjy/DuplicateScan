#pragma once
#include<QTableView>
#include "global.h"
class QStandardItemModel;
class QMenu;
class QAction;
class MySortFilterProxyModel;

class MyTableView :
	public QTableView
{
	Q_OBJECT
public:
	MyTableView(QWidget *parent = NULL);
	virtual ~MyTableView(void);
	void clearItem();
	bool writeResult(QMap<QString, QList<TableData> >&writeFileInfoMap,
		QString fileName = tr("result.txt"));
	
signals:
	void screenFileInfoMapSignal();
	
public slots:
	void threadFinished();
	void screenFileInfoMapSlot();
	void showContextMenu(const QPoint &);
	void deleteSelectedItem();
	void takeSelectedItem();
	void screenFileSize(int state,int value);
	void loadResult();
private:
	
	QStandardItemModel *m_pModel;
	MySortFilterProxyModel *m_pProxyModel;
	QMenu *m_pContextMenu;
	QAction *m_pOpenDir;

};

