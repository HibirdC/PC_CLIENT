#include "languetools.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	LangueTools w;
	w.show();
	return a.exec();
}
