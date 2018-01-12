#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QtGui>
#include <QtCore>
#include <QPushButton>


#include <block.h>


namespace Ui
{
class MainWindow;
}


class MainWindow : public QMainWindow
{
	Q_OBJECT

private:
	Ui::MainWindow							*ui;
	std::map<unsigned long long, Block*>	mBlock;
	QString									mBlockCss;
	unsigned long long						mID;
	QPoint									mPrevDragPos;
	QPoint									mDragPos;

public:
	explicit MainWindow(QWidget* parent = 0);

	~MainWindow();

	QString& getBlockCss();

protected:
	void keyPressEvent(QKeyEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;

public slots:
	void deleteBlock(const unsigned long long id);

private slots:
	void addBlock();

private:
	QString setupCss(const char* fileName);
};


#endif // MAINWINDOW_H
