#pragma once
#include<qsortfilterproxymodel.h>
class MySortFilterProxyModel :
	public QSortFilterProxyModel
{
public:
	MySortFilterProxyModel(QObject *parent);
	virtual ~MySortFilterProxyModel(void);
	void setMinSize(int size);
	int getMinSize();
	bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const;
	bool sizeInRange(int size) const;
	void reset();
private:
	int minSize;
};

