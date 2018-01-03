#include <QDebug>
#include <QFontMetrics>


#include "mainwindow.h"
#include "block.h"


Block::Block(const unsigned long long id, QWidget* parent)
:
QWidget(parent),
mID(id)
{
	// initialize the widget
	this->setStyleSheet("background-color:lightgray");

	// initialize the block
	mLayout = new QGridLayout(this);
	mLabel = new QLabel(this);

	// initialize the layout
	mLayout->setMargin(8);

	// set size policies
	mLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	mLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	// set default title
	mTitle = "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf";
	mLabel->setText(mTitle);

	// add stuff to widget
	mLayout->addWidget(mLabel, 0, 0, 3, 1);
	this->setLayout(mLayout);
}


void
Block::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		mDragPos = event->globalPos() - frameGeometry().topLeft();
		event->accept();
	}
	else if (event->button() == Qt::RightButton)
	{
		this->close();
		event->accept();
		((MainWindow*)this->parent())->deleteBlock(mID);
	}
	else if (event->button() == Qt::MiddleButton)
	{
		mTitle = "clicked";
		mLabel->setText(mTitle);
	}
}


void
Block::mouseMoveEvent(QMouseEvent *event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		this->move(event->globalPos() - mDragPos);
		event->accept();
	}
}
