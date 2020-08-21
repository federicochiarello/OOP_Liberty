#include <QApplication>

#include "view/view.h"
#include "view/taskslist.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
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

