#include <QApplication>


#include "model/model.h"
#include "controller/controller.h"
#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);

	Model m;
	Controller c(&m);
	View v(&c);
	c.setView(&v);

//	Controller c;
//	TextHolder v("prova");
//	TaskWidget v;
//	TaskPreview v;
//	TaskHolder v;
//	TasksListWidget v("Prova");
//	TasksList v;
//	DragDrop v;
//	ProjectView v;
//	View v;
	v.show();
	return app.exec();
}

