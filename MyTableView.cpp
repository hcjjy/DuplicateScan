#include "MyTableView.h"
#include "mainwindow.h"
#include <QtGui>
#include <QFile>
extern bool stopflag;
extern QList<QString> conditonsList;
extern QMultiMap<QString,QString>namesInfoMultiMap;
extern QMultiMap<QString,QString>MD5InfoMultiMap;
extern QMultiMap<qint64,QString>sizesInfoMultiMap;
extern std::multimap<QString,QString,cmp>resResult;
extern QMap<QString, QList<tableData> >fileInfoMap; 
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
	setContextMenuPolicy(Qt::CustomContextMenu);
	m_pContextMenu = new QMenu(this);

	m_pOpenDir = new QAction("open Directory",this);
	m_pContextMenu->addAction(m_pOpenDir);

	

	connect(this,SIGNAL(customContextMenuRequested(const QPoint &)),
		this,SLOT(showContextMenu(const QPoint &)));
	connect(this,SIGNAL(setModelSignal()),this,SLOT(setModelSlot()));
}


MyTableView::~MyTableView(void)
{
}

void MyTableView::screenItem()
{	
	QMultiMap<qint64,QString> sizesTempMap;
	QMultiMap<QString,QString> MD5TempMap;
	QMultiMap<QString,QString>::iterator iterName;
	QMultiMap<qint64,QString>::iterator iterSizes;
	QMultiMap<QString,QString>::iterator iterMD5;
	QFileInfo fileInfo;
	int cntName,cntSize,cntMD5,i;
	if (conditonsList.count("names"))
	{
		for (iterName=namesInfoMultiMap.begin();iterName!=namesInfoMultiMap.end();)
		{
			if (stopflag)
			{
				sizesTempMap.clear();
				MD5TempMap.clear();
				cntName = namesInfoMultiMap.count(iterName.key());
				if (cntName>1)
				{

					if (conditonsList.count("sizes"))
					{
						for (i=0;i<cntName;i++,iterName++)
						{
							fileInfo.setFile(iterName.value());
							sizesTempMap.insert(fileInfo.size(),iterName.value());
						}
						for (iterSizes=sizesTempMap.begin();iterSizes!=sizesTempMap.end();)

						{
							MD5TempMap.clear();
							cntSize = sizesTempMap.count(iterSizes.key());
							if (cntSize>1)
							{

								if (conditonsList.count("MD5"))
								{
									for (i=0;i<cntSize;i++,iterSizes++)
									{
										fileInfo.setFile(iterSizes.value());
										MD5TempMap.insert(MD5InfoMultiMap.key(iterSizes.value()),
											iterSizes.value());
									}
									for (iterMD5=MD5TempMap.begin();
										iterMD5!=MD5TempMap.end();)
									{
										cntMD5 = MD5TempMap.count(iterMD5.key());
										if (cntMD5>1)
										{
											for (i=0;i<cntMD5;i++,iterMD5++)
											{
												addOneItem(iterMD5.value(),MD5TempMap);
												//resResult.insert(std::make_pair(iterMD5.value(),
													//MD5TempMap.key(iterMD5.value())));
											}
										}
										else
										{
											iterMD5++;
										}
									}
								}
								else
								{
									for (i=0;i<cntSize;i++,iterSizes++)
									{
										addOneItem(iterSizes.value(),MD5InfoMultiMap);
										//resResult.insert(std::make_pair(iterSizes.value(),
											//MD5InfoMultiMap.key(iterSizes.value())));
									}
								}

							}
							else
							{
								iterSizes++;
							}
						}
					}
					else
					{
						if (conditonsList.count("MD5"))
						{
							for (i=0;i<cntName;i++,iterName++)
							{
								fileInfo.setFile(iterName.value());
								MD5TempMap.insert(MD5InfoMultiMap.key(iterName.value()),
									iterName.value());
							}
							//MD5
							for (iterMD5=MD5TempMap.begin();iterMD5!=MD5TempMap.end();)
							{
								cntMD5 = MD5TempMap.count(iterMD5.key());
								if (cntMD5>1)
								{
									for (i=0;i<cntMD5;i++,iterMD5++)
									{
										addOneItem(iterMD5.value(),MD5TempMap);
										//resResult.insert(std::make_pair(iterMD5.value(),
											//MD5TempMap.key(iterMD5.value())));
									}
								}
								else
								{
									iterMD5++;
								}
							}
						}
						else
						{
							for (i=0;i<cntName;i++,iterName++)
							{
								addOneItem(iterName.value(),MD5InfoMultiMap);
								//resResult.insert(std::make_pair(iterName.value(),
									//MD5InfoMultiMap.key(iterName.value())));
							}
						}
					}


				}
				else
				{
					iterName++;
				}
			}
			
				
		}
	}
	else
	{
		if(conditonsList.count("sizes"))
		{
			for (iterSizes=sizesInfoMultiMap.begin();iterSizes!=sizesInfoMultiMap.end();)
			{
				if (stopflag)
				{
					MD5TempMap.clear();
					cntSize = sizesInfoMultiMap.count(iterSizes.key());
					if (cntSize>1)
					{

						if (conditonsList.count("MD5"))
						{
							for (i=0;i<cntSize;i++,iterSizes++)
							{
								fileInfo.setFile(iterSizes.value());
								MD5TempMap.insert(MD5InfoMultiMap.key(iterSizes.value()),
									iterSizes.value());
							}
							for (iterMD5=MD5TempMap.begin();
								iterMD5!=MD5TempMap.end();)
							{
								cntMD5 = MD5TempMap.count(iterMD5.key());
								if (cntMD5>1)
								{
									for (i=0;i<cntMD5;i++,iterMD5++)
									{
										addOneItem(iterMD5.value(),MD5TempMap);
										//resResult.insert(std::make_pair(iterMD5.value(),
											//MD5TempMap.key(iterMD5.value())));
									}
								}
								else
								{
									iterMD5++;
								}
							}
						}
						else
						{
							for (i=0;i<cntSize;i++,iterSizes++)
							{
								addOneItem(iterSizes.value(),MD5InfoMultiMap);
								//resResult.insert(std::make_pair(iterSizes.value(),
									//MD5InfoMultiMap.key(iterSizes.value())));
							}
						}
					}
					else
					{
						iterSizes++;
					}
				}
				
			}
		}
		else
		{
			if (stopflag)
			{
				if (conditonsList.count("MD5"))
				{
					for (iterMD5=MD5InfoMultiMap.begin();iterMD5!=MD5InfoMultiMap.end();)
					{
						cntMD5 = MD5InfoMultiMap.count(iterMD5.key());
						if (cntMD5>1)
						{
							for (i=0;i<cntMD5;i++,iterMD5++)
							{
								qDebug()<<iterMD5.value()<<endl;
								addOneItem(iterMD5.value(),MD5InfoMultiMap);
								//resResult.insert(std::make_pair(iterMD5.value(),
									//MD5InfoMultiMap.key(iterMD5.value())));
							}
						}
						else
						{
							iterMD5++;
						}
					}
				}
				else
				{
					return;
				}
			}
			
		}
	}
}

void MyTableView::addOneItem(QString file,QMultiMap<QString,QString> &MD5Map)
{
	QFileInfo fileInfo;
	fileInfo.setFile(file);
	int row = m_pModel->rowCount();
	m_pModel->insertRow(row);
	m_pModel->setItem(row,0,new QStandardItem(fileInfo.fileName()));
	m_pModel->setItem(row,1,new QStandardItem(fileInfo.path()));
	m_pModel->setItem(row,2,new QStandardItem(QString::number(fileInfo.size())));
	m_pModel->setItem(row,3,new QStandardItem(fileInfo.lastRead().toString()));
	m_pModel->setItem(row,4,new QStandardItem(MD5Map.key(file)));
}

void MyTableView::clearItem()
{
	m_pModel->clear();
}

void MyTableView::clearModel()
{
	setModel(NULL);
}

void MyTableView::setModelSlot()
{

	m_pModel->setColumnCount(5);
	m_pModel->setHeaderData(0,Qt::Horizontal,tr("FileName"));
	m_pModel->setHeaderData(1,Qt::Horizontal,tr("Path"));
	m_pModel->setHeaderData(2,Qt::Horizontal,tr("Size"));
	m_pModel->setHeaderData(3,Qt::Horizontal,tr("Date"));
	m_pModel->setHeaderData(4,Qt::Horizontal,tr("MD5"));
	setModel(m_pModel);
	
	/*
	QFileInfo fileInfo;
	std::multimap<QString,QString,cmp>::iterator iter= resResult.begin();
	for (;iter!=resResult.end();iter++)
	{
		fileInfo.setFile(iter->first);
		int row = m_pModel->rowCount();
		m_pModel->insertRow(row);
		m_pModel->setItem(row,0,new QStandardItem(fileInfo.fileName()));
		m_pModel->setItem(row,1,new QStandardItem(fileInfo.path()));
		m_pModel->setItem(row,2,new QStandardItem(QString::number(fileInfo.size())));
		m_pModel->setItem(row,3,new QStandardItem(fileInfo.lastRead().toString()));
		m_pModel->setItem(row,4,new QStandardItem(iter->second));
	}*/

	//method 2
	
	QMap<QString, QList<tableData> >::iterator iterMap;
	QList<tableData>::iterator iterList;
	QList<tableData> dataList;
	int tableRow=0;
	for (iterMap = fileInfoMap.begin();iterMap!= fileInfoMap.end();iterMap++)
	{
		dataList = iterMap.value();
		if (dataList.count()>1)
		{
			tableRow+=dataList.count();
		}
	}
	m_pModel->setRowCount(tableRow);
	//qDebug()<<"tableRow = "<<tableRow<<endl;
	int row =0;
	for (iterMap = fileInfoMap.begin();iterMap!= fileInfoMap.end();iterMap++)
	{
		dataList = iterMap.value();
		if (dataList.count()>1)
		{
			for (iterList=dataList.begin();iterList!= dataList.end();iterList++)
			{
				tableData tData = *iterList;
				QStandardItem *p=NULL;

				p= new QStandardItem(tData.fileName);
				p->setEditable(false);
				m_pModel->setItem(row,0,p);

				p= new QStandardItem(tData.filePath);
				p->setEditable(false);
				m_pModel->setItem(row,1,p);

				p= new QStandardItem(QString::number(tData.fileSize));
				p->setEditable(false);
				m_pModel->setItem(row,2,p);

				p= new QStandardItem(tData.fileTime.toString());
				p->setEditable(false);
				m_pModel->setItem(row,3,p);

				p= new QStandardItem(tData.fileMD5);
				p->setEditable(false);
				m_pModel->setItem(row,4,p);

				row++;
			}
		}
	}

	setSelectionBehavior(QAbstractItemView::SelectRows);//set all a row selected
	verticalHeader()->setVisible(false); //hide column header
	this->setShowGrid(false); //hide line

}

void MyTableView::threadFinished()
{
	emit setModelSignal();
}

void MyTableView::showContextMenu(const QPoint &pos)
{
	QModelIndex modelIndex=indexAt(pos);
	if (modelIndex.isValid())
	{
		QAction *checkAciton =m_pContextMenu->exec(QCursor::pos());
		if (checkAciton==m_pOpenDir)
		{
			int row = modelIndex.row();
			QStandardItem *itemRoot = m_pModel->item(row,1);
			QStandardItem *itemFile = m_pModel->item(row,0);	
			QString fileDir = itemRoot->text()+"/"+itemFile->text();
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
		int row = modelIndexList.front().row();
		QStandardItem *itemRoot = m_pModel->item(row,1);
		QStandardItem *itemFile = m_pModel->item(row,0);	
		QString fileDir = itemRoot->text()+"/"+itemFile->text();
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
		int row = modelIndexList.front().row();
		m_pModel->takeRow(row);
	}
}


