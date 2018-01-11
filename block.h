#ifndef BLOCK_H
#define BLOCK_H


#include <QWidget>
#include <QLabel>
#include <QMouseEvent>
#include <QGridLayout>
#include <QPushButton>


class Block : public QWidget
{
	Q_OBJECT

private:
	static constexpr int eTitleMinSize = 32;	// If the title is less than eTitleMinSize amount of characters, it would fill the surroundings with white spaces
	static constexpr int eTitleFont = 10;		// The extra font size of the title compared to the other labels
	static constexpr int eMinFont = 20;			// The minimum font before the label disappear

	QGridLayout*		mLayout;
	QLabel*				mTitle;
	QLabel*				mBackground;
	QPoint				mDragPos;
	QString				mTitleText;
	unsigned long long	mID;

	QPushButton*		mAddIn;
	QPushButton*		mAddOut;
	QPushButton*		mPopIn;
	QPushButton*		mPopOut;

	std::vector<QLabel*>mInput;
	std::vector<QLabel*>mOutput;

public:
	Block(const unsigned long long id, QWidget *parent = 0);

	~Block();

public slots:
	void updateText(const QString& str);

protected:
	void mouseMoveEvent(QMouseEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void wheelEvent(QWheelEvent* event);
	void resizeEvent(QResizeEvent*);

private slots:
	void adjustLabelSize();
	void addInput();
	void addOutput();
	void popInput();
	void popOutput();
};


#endif // BLOCK_H
