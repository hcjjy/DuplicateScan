#pragma once
#include<QtGui/QFrame>
class QLabel;
class QCheckBox;
class SimpleMatchConditions :
	public QFrame
{
	Q_OBJECT
public:
	SimpleMatchConditions(QWidget * parent = NULL);
	virtual ~SimpleMatchConditions(void);
	QMap<QString , Qt::CheckState>getConditionsMap();
protected:
	virtual void resizeEvent(QResizeEvent* event);
private:
	QLabel *m_pTitleLabel;
	QCheckBox *m_pNamesIdentical;
	QCheckBox *m_pSizesIdentical;
	QCheckBox *m_pMD5Identical;
};

