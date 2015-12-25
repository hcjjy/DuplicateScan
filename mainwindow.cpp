#include "mainwindow.h"
#include "DuplicateScan.h"
#include "OptionsSetting.h"
#include "ProgressBarContainer.h"
#include "ReadThread.h"
#include "caculateMD5.h"
#include <QtGui>
QMultiMap<QString,QString>namesInfoMultiMap;
QMultiMap<QString,QString>MD5InfoMultiMap;
QMultiMap<qint64,QString>sizesInfoMultiMap;
QList<QString> conditonsList;
QList<QString> fileDirList;
bool stopflag=true;

QMap<QString, QList<tableData> >fileInfoMap;  //new method resResult
std::multimap<QString,QString,cmp>resResult;//old method resResult
MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	ui.setupUi(this);
	resize(800,600);
	setMinimumHeight(170);
	DuplicateScan *duplicateScan = new DuplicateScan();
	OptionsSetting *optionsSetting = new OptionsSetting();
	m_pTabWidget = new QTabWidget(this);

	m_pTabWidget->addTab(duplicateScan,tr("DuplicateScan"));
	m_pTabWidget->addTab(optionsSetting,tr("OptionsSetting"));
	m_pTabWidget->setCurrentIndex(1);

	m_pRun = new QPushButton(tr("Run"),this);
	m_pCancel = new QPushButton(tr("Cancel"),this);

	m_pProgressBarContainer = new ProgressBarContainer(this);

	readFile = new ReadThread();
	readFile->RevPtr(this);

	connect(m_pRun,SIGNAL(clicked()),this,SLOT(runPre()));
	connect(m_pCancel,SIGNAL(clicked()),this,SLOT(canCelRun()));
	connect(readFile,SIGNAL(finished()),duplicateScan,SLOT(threadFinished()));
	connect(readFile,SIGNAL(finished()),this,SLOT(canCelRun()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::resizeEvent( QResizeEvent *event )
{
	m_pTabWidget->setGeometry(0,0,width(),height()-160);
	m_pRun->setGeometry(20,height()-100,80,20);
	m_pCancel->setGeometry(20,height()-50,80,20);

	m_pProgressBarContainer->setGeometry(150,height()-140,width()-160,130);

}

void MainWindow::runPre()
{
	OptionsSetting *optionsSetting = (OptionsSetting*)(m_pTabWidget->widget(1));
	QMap<QString , Qt::CheckState> fileDirMap= optionsSetting->getFileDirMap();

	QMap<QString , Qt::CheckState> conditonsMap= optionsSetting->getConditionsMap();

	if(!checkoutData(fileDirMap,conditonsMap))
		return;

	DuplicateScan *duplicateScan = (DuplicateScan*)(m_pTabWidget->widget(0));
	duplicateScan->clearModel();
	m_pTabWidget->setCurrentIndex(0);

	m_pRun->setEnabled(false);
	stopflag=true;
	
	readFile->start();
}


bool MainWindow::checkoutData( QMap<QString , Qt::CheckState>fileDirMap ,
	QMap<QString , Qt::CheckState> conditonsMap)
{
	fileDirList.clear();
	conditonsList.clear();
	
	QMap<QString , Qt::CheckState>::iterator iter;
	for (iter = fileDirMap.begin();iter!=fileDirMap.end();iter++)
	{
		if (iter.value()==Qt::Checked)
		{
			fileDirList.push_back(iter.key());
		}
	}
	if (fileDirList.isEmpty())
	{
		QMessageBox::information(this,tr("information"),
			tr("there are no file to be Checked\n please go optionSetting Checked."));
		return false;
	}

	for (iter = conditonsMap.begin();iter!=conditonsMap.end();iter++)
	{
		if (iter.value()==Qt::Checked)
		{
			conditonsList.push_back(iter.key());
		}
	}
	if (conditonsList.isEmpty())
	{
		QMessageBox::information(this,tr("information"),
			tr("You have to select at least one comparement criterion."));
		return false;
	}
	return true;
}



void MainWindow::run()
{
	DuplicateScan *duplicateScan = (DuplicateScan*)(m_pTabWidget->widget(0));
	duplicateScan->clearItem();
	fileInfoMap.clear();
	//resResult.clear();
	foreach(QString path,fileDirList)
	{
		dirTraverse(path);
	}															
 	
	if (stopflag)
	{
		//duplicateScan->screenItem();
	}
}

void MainWindow::dirTraverse( QString path)
{
	if (stopflag)
	{
		QDir dir(path);
		foreach(QFileInfo fileInfo,dir.entryInfoList())
		{
			if(fileInfo.isFile())
			{
				//static int cnt =0;
				//cnt++;
				//qDebug()<<"cnt = "<<cnt<<endl;
				QString MD5 = MD5_file(fileInfo.absoluteFilePath().toLocal8Bit().data(),32);

				/*namesInfoMultiMap.insert(fileInfo.fileName(),fileInfo.absoluteFilePath());
				sizesInfoMultiMap.insert(fileInfo.size(),fileInfo.absoluteFilePath());
				MD5InfoMultiMap.insert(MD5,fileInfo.absoluteFilePath());*/

				//method 2
				QString strKey ="";
				if (conditonsList.count("names"))
				{
					strKey+=fileInfo.fileName()+":";
				}
				if (conditonsList.count("sizes"))
				{
					strKey+=QString::number(fileInfo.size())+":";
					
				}
				if (conditonsList.count("MD5"))
				{
					strKey+=MD5+":";
				}
				QList<tableData> listDir;
				tableData tData;
				listDir.clear();

				if (fileInfoMap.count(strKey)>0)
				{
					
					listDir = fileInfoMap.value(strKey);
					
				}
				tData.fileName = fileInfo.fileName();
				tData.filePath = fileInfo.absolutePath();
				tData.fileSize = fileInfo.size();
				tData.fileMD5 = MD5;
				tData.fileTime = fileInfo.lastModified();
				listDir.push_back(tData);
				fileInfoMap.insert(strKey,listDir);
			}
			else
			{
				//�ڸ����ļ�ϵͳ��ͨ�����������ǰĿ¼���ϲ�Ŀ¼,��Ҫ���˵�
				if (fileInfo.fileName()=="."||fileInfo.fileName()=="..")
				{
					continue;
				}
				//qDebug() << "Entry Dir" << fileInfo.absoluteFilePath();
				dirTraverse(fileInfo.absoluteFilePath());
			}
		}
	}
	
}

void MainWindow::canCelRun()
{
	
	
	/*namesInfoMultiMap.clear();
	MD5InfoMultiMap.clear();
	sizesInfoMultiMap.clear();*/
	
	m_pRun->setEnabled(true);
	stopflag=false;
}