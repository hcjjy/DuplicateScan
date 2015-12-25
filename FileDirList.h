#pragma once
#include <QtGui/QFrame>
class QFrame;
class QListWidget;
class QPushButton;
class QLabel;
class FileDirList :
	public QFrame
{
	Q_OBJECT
public:
	FileDirList(QWidget * parent = NULL);
	virtual ~FileDirList(void);
	QMap<QString,Qt::CheckState> getFileDirMap();
protected:
	virtual void resizeEvent(QResizeEvent *event);
public slots:
	void addFileDir();
	void removeFileDir();
private:
	QFrame *m_pFrame;
	QLabel *m_pTitleLabel;
	QListWidget *m_pFileDirList;
	QPushButton *m_pAddFileDir;
	QPushButton *m_pRemoveFileDir;
};

