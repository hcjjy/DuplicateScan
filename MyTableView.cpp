#include "MyTableView.h"
#include "global.h"
#include "MySortFilterProxyModel.h"
#include <QtGui>
#include <QFile>
#include <QDataStream>
void OpenExplorerAndSelectFile(const QString &filePath)
{
	QString path = QDir::toNativeSeparators(filePath);
	QProcess precoss;
#ifdef Q_OS_WIN32
	QProcess::execute("explorer", QStringList() << "/e,/select," << path);
#else
	QProcess::execute("open", QStringList() << "/e,/select,"<< filePath);
	//	string strPath = filePath.toLocal8Bit().data();
	//	NSString *fullPath = [NSString stringWithUTF8String:strPath.c_str()];
	//	return [[NSWorkspace sharedWorkspace] selectFile:fullPath inFileViewerRootedAtPath:nil];
#endif
}
MyTableView::MyTableView( QWidget *parent /*= NULL*/ )
	:QTableView(parent)
{
	m_pModel = new QStandardItemModel();
	/*setModel(m_pModel);*/
	m_pProxyModel = new MySortFilterProxyModel(this);
	m_pProxyModel->setSourceModel(m_pModel);
	setModel(m_pProxyModel);

	setSelectionBehavior(QAbstractItemView::SelectRows);//set all a row selected
	verticalHeader()->setVisible(false); //hide column header
	this->setShowGrid(false); //hide line
	setAlternatingRowColors(true);

	setContextMenuPolicy(Qt::CustomContextMenu);
	m_pContextMenu = new QMenu(this);

	m_pOpenDir = new QAction("open Directory",this);
	m_pContextMenu->addAction(m_pOpenDir);

	setSortingEnabled(true);

	connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),
		this,SLOT(showContextMenu(const QPoint &)));
	connect(this,SIGNAL(screenFileInfoMapSignal()),this,SLOT(screenFileInfoMapSlot()));
}


MyTableView::~MyTableView(void)
{
}

void MyTableView::clearItem()
{
	m_pModel->clear();
}

bool MyTableView::writeResult( QMap<QString, QList<TableData> >&writeFileInfoMap,
	QString fileName /* = tr("result.txt") */)
{
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly))
	{
		return false;
	}
	QDataStream out(&file);
	out.setVersion(QDataStream::Qt_4_7);//统一输入输出流接口
	out<<writeFileInfoMap;
	file.close();
	return true;
}

void MyTableView::screenFileInfoMapSlot()
{
	QMap<QString, QList<TableData> >writeFileInfoMap;
	QMap<QString, QList<TableData> >::iterator iterMap;
	QList<TableData> dataList;

	for (iterMap = fileInfoMap.begin();iterMap!= fileInfoMap.end();iterMap++)
	{
		dataList = iterMap.value();
		if (dataList.count()>1)
		{
			writeFileInfoMap.insert(iterMap.key(),dataList);
		}
	}
	writeResult(writeFileInfoMap);
}
void MyTableView::loadResult()
{
	QMap<QString, QList<TableData> >loadFileInfoMap;
	QMap<QString, QList<TableData> >::iterator iterMap;
	QList<TableData>::iterator iterList;
	QList<TableData> dataList;
	QStandardItem *p;
	int row,tableRow;
	QString dataFlag;
	QString fileName = QFileDialog::getOpenFileName(this,tr("select Folds"),"./","*.txt");
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly))
		return;
	clearItem();
	QDataStream in(&file);
	in.setVersion(QDataStream::Qt_4_7);
	
	m_pModel->setColumnCount(5);
	m_pModel->setHeaderData(0,Qt::Horizontal,tr("FileName"));
	m_pModel->setHeaderData(1,Qt::Horizontal,tr("Path"));
	m_pModel->setHeaderData(2,Qt::Horizontal,tr("Size"));
	m_pModel->setHeaderData(3,Qt::Horizontal,tr("Date"));
	m_pModel->setHeaderData(4,Qt::Horizontal,tr("MD5"));

	in>>loadFileInfoMap;
	tableRow =0;
	for (iterMap = loadFileInfoMap.begin();iterMap!= loadFileInfoMap.end();iterMap++)
	{
		dataList = iterMap.value();
		tableRow+=dataList.count();
	}
	m_pModel->setRowCount(tableRow);
	row = 0;
	for (iterMap = loadFileInfoMap.begin();iterMap!= loadFileInfoMap.end();iterMap++)
	{
		dataList = iterMap.value();
		for (iterList=dataList.begin();iterList!= dataList.end();iterList++)
		{
			
			p= new QStandardItem(iterList->fileName);
			p->setEditable(false);
			m_pModel->setItem(row,0,p);

			p= new QStandardItem(iterList->filePath);
			p->setEditable(false);
			m_pModel->setItem(row,1,p);

			p= new QStandardItem(QString::number(iterList->fileSize));
			p->setData(iterList->fileSize,Qt::DisplayRole);//设置排序规则
			p->setEditable(false);
			m_pModel->setItem(row,2,p);

			p= new QStandardItem(iterList->fileTime.toString());
			p->setData(iterList->fileTime,Qt::DisplayRole);//设置排序规则
			p->setEditable(false);
			m_pModel->setItem(row,3,p);

			p= new QStandardItem(iterList->fileMD5);
			p->setEditable(false);
			m_pModel->setItem(row,4,p);

			row++;

			//QApplication::processEvents();//让界面可以不至于卡死
		}
	}
}
void MyTableView::threadFinished()
{
	emit screenFileInfoMapSignal();
}
void MyTableView::showContextMenu(const QPoint &pos)
{
	QModelIndex proxyIndex=indexAt(pos);
	if (proxyIndex.isValid())
	{
		QAction *checkAciton =m_pContextMenu->exec(QCursor::pos(),0);

		if (checkAciton==m_pOpenDir)
		{
			QModelIndex sourceIndex = m_pProxyModel->mapToSource(proxyIndex);
			int row = sourceIndex.row();

			QStandardItem *itemRoot = m_pModel->item(row,1);
			QStandardItem *itemFile = m_pModel->item(row,0);
			QString fileDir = itemRoot->text();
			QDir dir(fileDir);
			if(!dir.isRoot())
				fileDir+="/";
			fileDir+=itemFile->text();

			OpenExplorerAndSelectFile(fileDir);
		}
	}
}
void MyTableView::deleteSelectedItem()
{
	QModelIndexList modelIndexList = this->selectedIndexes();
	if (modelIndexList.empty())
	{
		QMessageBox::about(this,tr("warning"),tr("you can't select any item."));
	}
	else
	{
		QModelIndex frontProxyIndex = modelIndexList.front();
		QModelIndex frontSourceIndex = m_pProxyModel->mapToSource(frontProxyIndex);
		int row = frontSourceIndex.row();

		QStandardItem *itemRoot = m_pModel->item(row,1);
		QStandardItem *itemFile = m_pModel->item(row,0);
		QString fileDir = itemRoot->text();
		QDir dir(fileDir);
		if(!dir.isRoot())
			fileDir+="/";
		fileDir+=itemFile->text();
		QFile file(fileDir);

		if(file.remove())
		{
			m_pModel->removeRow(row);
			QMessageBox::about(this,tr("result"),tr("successful"));
		}
		else
		{
			QMessageBox::about(this,tr("result"),tr("fail"));
		}
	}
}

void MyTableView::takeSelectedItem()
{
	QModelIndexList modelIndexList = this->selectedIndexes();
	if (modelIndexList.empty())
	{
		QMessageBox::about(this,tr("warning"),tr("you can't select any item."));
	}
	else
	{	
		QModelIndex frontProxyIndex = modelIndexList.front();
		QModelIndex frontSourceIndex = m_pProxyModel->mapToSource(frontProxyIndex);
		int row = frontSourceIndex.row();

		m_pModel->takeRow(row);
	}
}

void MyTableView::screenFileSize( int state,int value)
{
	if (state == 0)
	{
		m_pProxyModel->setMinSize(-1);
		m_pProxyModel->reset();
	}
	if (state == 2)
	{
		m_pProxyModel->setMinSize(value);
		m_pProxyModel->reset();
	}
}
