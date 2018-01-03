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
	unsigned long long						mID;

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

protected:
	void keyPressEvent(QKeyEvent *event);

public slots:
	void deleteBlock(const unsigned long long id);

private slots:
	void addBlock();

private:
};


#endif // MAINWINDOW_H
