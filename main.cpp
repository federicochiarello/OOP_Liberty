#include <QApplication>

#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Model m;
	Controller c(&m);
	View v;
	c.setView(&v);
	v.show();
	return app.exec();
}

