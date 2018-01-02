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
	Ui::MainWindow		*ui;
	std::vector<Block*>	mBlock;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event);

private slots:
	void addBlock();

private:
};


#endif // MAINWINDOW_H
