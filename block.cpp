#include <QDebug>
#include <QFont>
#include <QFontMetrics>


#include "block.h"


Block::Block(QWidget* parent)
:
QWidget(parent)
{
	mLabel = new QLabel(this);
	mTitle = "asdfasdfasdfasdfasdfasdfasdfasdf";
	mLabel->setText(mTitle);
	updateSize();
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
	}
	else if (event->button() == Qt::MiddleButton)
	{
		mTitle = "clicked";
		mLabel->setText(mTitle);
		updateSize();
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


QSize
Block::updateSize()
{
	QSize size(this->fontMetrics().width(mTitle), this->fontMetrics().height());
	this->move(this->pos().x() + (this->size().width() >> 1) - (size.width() >> 1), this->pos().y() + (this->size().height() >> 1) - (size.height() >> 1));
	mLabel->resize(size);
	this->resize(size);
	return size;
}
