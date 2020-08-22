#include <QApplication>
/*
#include "vista.h"
#include "model.h"
#include "controller.h"
*/
#include "view/view.h"
#include "view/taskslist.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

    /*
    Model m;
    Controller c(&m);
    Vista v(&c);
    c.setView(&v);

    v.show();
    */
//	Controller c;
//	TextHolder t("prova");
	TaskWidget t;
//	TaskPreview t;
//	TaskHolder t;
//	TasksListWidget t("Prova");
//	TasksList t;
//	DragDrop t;
//	ProjectView t;
//	View t;
	t.show();
	return app.exec();
}

