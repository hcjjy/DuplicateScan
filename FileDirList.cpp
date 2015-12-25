#include "FileDirList.h"
#include<QtGui>
FileDirList::FileDirList( QWidget * parent /*= NULL*/ )
	:QFrame(parent)
{
	this->setFrameStyle(QFrame::WinPanel|QFrame::Raised);
	m_pTitleLabel = new QLabel(tr("FileDir"),this);
	m_pFileDirList = new QListWidget(this);
	
	m_pAddFileDir = new QPushButton(tr("+"),this);
	m_pRemoveFileDir = new QPushButton(tr("-"),this);
	connect(m_pAddFileDir,SIGNAL(clicked()),this,SLOT(addFileDir()));
	connect(m_pRemoveFileDir,SIGNAL(clicked()),this,SLOT(removeFileDir()));
}


FileDirList::~FileDirList(void)
{
	
}

void FileDirList::resizeEvent( QResizeEvent *event )
{
	m_pTitleLabel->setGeometry(10,10,40,10);
	m_pFileDirList->setGeometry(10,30,220,120);
	m_pAddFileDir->setGeometry(230,150,30,20);
	m_pRemoveFileDir->setGeometry(265,150,30,20);
}

void FileDirList::addFileDir()
{
	QString fileName = QFileDialog::getExistingDirectory(this,tr("select Folds"));
	QList<QListWidgetItem *>sameFileName = m_pFileDirList->findItems(fileName,
															Qt::MatchContains);
	if (sameFileName.isEmpty())
	{
		if (!fileName.isEmpty())
		{
			QListWidgetItem * item = new QListWidgetItem(fileName);
			item->setCheckState(Qt::Checked);
			item->setSelected(true);
			m_pFileDirList->addItem(item);
		}
	}
	else
	{
		QMessageBox::warning(this,tr("Warning"),tr("FileDir is exits or Contained."));
	}
	
	m_pFileDirList->setCurrentRow(0,QItemSelectionModel::Select);
}

void FileDirList::removeFileDir()
{

	m_pFileDirList->removeItemWidget( m_pFileDirList->currentItem());
	delete m_pFileDirList->currentItem();//must be do "delete",otherwise in vain
}



QMap<QString,Qt::CheckState> FileDirList::getFileDirMap()
{
	QMap<QString,Qt::CheckState> fileDirList;
	for (int i=0;i<m_pFileDirList->count();i++)
	{
		QListWidgetItem *fileDirItem = m_pFileDirList->item(i);
		fileDirList.insert(fileDirItem->text(),fileDirItem->checkState());
	}
	return fileDirList;
}


