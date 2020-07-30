#include <QApplication>

#include "view/view.h"
#include "view/taskslist.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	//Controller c;
	//View t;
	//TaskHolder t;
	//TasksListWidget t("Prova");
	TasksList t;
	//TaskWidget t;
	//TextHolder t("prova");
	//ProjectView t;
	t.show();
	return app.exec();
}

