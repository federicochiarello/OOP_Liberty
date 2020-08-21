#include <QApplication>
/*
#include "vista.h"
#include "model.h"
#include "controller.h"
*/

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

    /*
    Model m;
    Controller c(&m);
    Vista v(&c);
    c.setView(&v);

    v.show();
    */

	return app.exec();
}

