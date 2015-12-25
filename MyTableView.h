#pragma once
#include<QTableView>
#include <QFileInfo>
class QStandardItemModel;
class QMenu;
class QAction;
class MyTableView :
	public QTableView
{
	Q_OBJECT
public:
	MyTableView(QWidget *parent = NULL);
	virtual ~MyTableView(void);
	void screenItem();
	void addOneItem(QString file,QMultiMap<QString,QString> &MD5Map);
	void clearItem();
	void clearModel();

signals:
	void setModelSignal();
	
public slots:
	void setModelSlot();
	void threadFinished();
	void showContextMenu(const QPoint &);
	void deleteSelectedItem();
	void takeSelectedItem();
private:
	
	QStandardItemModel *m_pModel;
	QMenu *m_pContextMenu;
	QAction *m_pOpenDir;
};

