#include <QApplication>

#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Controller c;
	View v(&c);
	v.show();
	return app.exec();
}

