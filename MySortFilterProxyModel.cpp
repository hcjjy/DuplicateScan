#include "MySortFilterProxyModel.h"

MySortFilterProxyModel::MySortFilterProxyModel( QObject *parent )
	:QSortFilterProxyModel(parent)
{
	setDynamicSortFilter(true);
}

MySortFilterProxyModel::~MySortFilterProxyModel(void)
{
}

void MySortFilterProxyModel::setMinSize( int size )
{
	this->minSize = size;
}

int MySortFilterProxyModel::getMinSize()
{
	return minSize;
}

bool MySortFilterProxyModel::filterAcceptsRow( int source_row, const QModelIndex &source_parent )const
{
	QModelIndex index2 = sourceModel()->index(source_row,2,source_parent);
	return sizeInRange(sourceModel()->data(index2).toInt());
}

bool MySortFilterProxyModel::sizeInRange( int size ) const
{
	return size >= minSize;
}

void MySortFilterProxyModel::reset()
{
	QSortFilterProxyModel::reset();
}

