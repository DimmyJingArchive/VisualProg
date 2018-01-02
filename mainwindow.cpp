#include <QDebug>


#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	connect(ui->actionExit, SIGNAL(triggered(bool)), this, SLOT(close()));
	connect(ui->actionAddCodeblock, SIGNAL(triggered(bool)), this, SLOT(addBlock()));
}


MainWindow::~MainWindow()
{
	delete ui;
}


void
MainWindow::keyPressEvent(QKeyEvent *event)
{
	if (event->text() == "\u0001")
	{
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
	Block *elem = new Block(this);
	elem->show();
	elem->move(QCursor::pos() - frameGeometry().topLeft());
	elem->move(elem->pos().x() - (elem->size().width() >> 1), (elem->pos().y() - this->style()->pixelMetric(QStyle::PM_TitleBarHeight) - (elem->size().height() >> 1)));
	mBlock.push_back(elem);
}
