#include "StudentMgr.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	StudentMgr w;
	w.show();
	return a.exec();
}
