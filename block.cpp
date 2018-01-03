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
	mLabel->setAlignment(Qt::AlignCenter);
	mButton1 = new QPushButton("Hello", this);
	mButton2 = new QPushButton("Hello", this);
	mButton3 = new QPushButton("Hello", this);

	// initialize the layout
	mLayout->setMargin(8);

	// set size policies
	mLayout->setSizeConstraint(QLayout::SetMinAndMaxSize);
	mLabel->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Preferred);

	// set default title
	mTitle = "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf";
	mLabel->setText(mTitle);

	// add stuff to widget
	mLayout->addWidget(mLabel, 0, 0, 1, 3, Qt::AlignCenter);
	mLayout->addWidget(mButton1, 1, 0);
	mLayout->addWidget(mButton2, 1, 1);
	mLayout->addWidget(mButton3, 1, 2);

	this->setLayout(mLayout);
}


void
Block::mousePressEvent(QMouseEvent* event)
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
		mTitle = "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdf";
		//mTitle = "a";
		mLabel->setText(mTitle);
		this->adjustSize();
	}
}


void
Block::mouseMoveEvent(QMouseEvent* event)
{
	if (event->buttons() & Qt::LeftButton)
	{
		this->move(event->globalPos() - mDragPos);
		event->accept();
	}
}


void
Block::wheelEvent(QWheelEvent* event)
{
	QFont font = mLabel->font();
	font.setPointSize(font.pointSize() + ((event->delta() / 120) * 8));
	mLabel->setFont(font);
	mButton1->setFont(font);
	mButton2->setFont(font);
	mButton3->setFont(font);
	this->adjustSize();
}
