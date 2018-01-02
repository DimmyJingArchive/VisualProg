#ifndef BLOCK_H
#define BLOCK_H


#include <QWidget>
#include <QtGui>
#include <QLabel>
#include <QMouseEvent>


class Block : public QWidget
{
private:
	QLabel*	mLabel;
	QPoint	mDragPos;
	QString	mTitle;

public:
	Block(QWidget *parent = 0);

private slots:
	QSize updateSize();

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
};


#endif // BLOCK_H
