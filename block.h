#ifndef BLOCK_H
#define BLOCK_H


#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>


class Block : public QWidget
{
private:
	QGridLayout*	mLayout;
	QLabel*			mLabel;
	QPoint			mDragPos;
	QString			mTitle;

public:
	Block(QWidget *parent = 0);

protected:
	void mouseMoveEvent(QMouseEvent *event);
	void mousePressEvent(QMouseEvent *event);
};


#endif // BLOCK_H