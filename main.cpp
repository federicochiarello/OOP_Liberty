#include <QApplication>

#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	//Controller c;
	//View t;
	//TaskHolder t;
	TasksList t(nullptr, "Inserire nome lista");
	//TaskWidget t;
	//TextHolder t("prova");
	t.show();
	return app.exec();
}

