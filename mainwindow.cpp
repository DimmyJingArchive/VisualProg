#include <QDebug>


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow),
	mID(0)
{
	ui->setupUi(this);

	// setup menu and canvas
	this->setObjectName("MainWindow");
	ui->menuBar->setObjectName("MainWindowMenuBar");
	for (auto& i : ui->menuBar->actions()) i->setObjectName("MainWindowAction");
	delete ui->mainToolBar;

	// connect actions
	connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(ui->actionAddCodeblock, SIGNAL(triggered(bool)), this, SLOT(addBlock()));

	// setup css
	mBlockCss = setupCss("Block.css");
	this->setStyleSheet(setupCss("Main.css"));
}


MainWindow::~MainWindow()
{
	delete ui;
}


QString&
MainWindow::getBlockCss()
{
	return mBlockCss;
}


void
MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->text() == "\u0001")
	{
		// <c-a>
		addBlock();
		event->accept();
	}
	else
	{
		qDebug() << event->text();
	}
}


void
MainWindow::addBlock()
{
	Block *elem = new Block(mID++, this);
	elem->show();
	elem->move(QCursor::pos() - frameGeometry().topLeft());
	elem->move(elem->pos().x() - (elem->size().width() >> 1), (elem->pos().y() - this->style()->pixelMetric(QStyle::PM_TitleBarHeight) - (elem->size().height() >> 1)));
	mBlock[mID] = elem;
}


void
MainWindow::deleteBlock(const unsigned long long id)
{
	mBlock.erase(id);
}


QString
MainWindow::setupCss(const char *fileName)
{
	// Read file
	QString name(":/Resource/Resource/");
	name += fileName;
	QFile file(name);
	file.open(QIODevice::ReadOnly);
	QString rawData = file.readAll();
	file.close();
	return rawData;
}




















