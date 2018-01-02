#include "mainwindow.h"
#include <QApplication>


#include "block.h"


int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;
	w.setWindowTitle("VisualProg");
	w.show();

	return a.exec();
}
