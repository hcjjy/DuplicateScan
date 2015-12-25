#pragma once
#include<QtGui/QWidget>
class SimpleMatchConditions;
class FileDirList;
class QListWidget;
class OptionsSetting :
	public QWidget
{
public:
	OptionsSetting(QWidget *parent = NULL);
	virtual ~OptionsSetting(void);
	QMap<QString , Qt::CheckState> getConditionsMap();
	QMap<QString , Qt::CheckState> getFileDirMap();
protected:
	virtual void resizeEvent(QResizeEvent *event);
private:
	SimpleMatchConditions *m_pConditions;
	FileDirList *m_pFileDirList;
};

