#ifndef BLOCK_H
#define BLOCK_H


#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QPushButton>


class Block : public QWidget
{
private:
	QGridLayout*		mLayout;
	QLabel*				mLabel;
	QPoint				mDragPos;
	QString				mTitle;
	unsigned long long	mID;

	QPushButton*		mButton1;
	QPushButton*		mButton2;
	QPushButton*		mButton3;

public:
	Block(const unsigned long long id, QWidget *parent = 0);

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
};


#endif // BLOCK_H
