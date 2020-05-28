#include <QApplication>

#include "view/view.h"

int main(int argc, char *argv[]) {
	QApplication app(argc, argv);
	Controller c;
	//View t(&c);
	TaskHolder t;
	//TasksList t;
	//TaskWidget t;
	//TextHolder t("prova");
	t.show();
	return app.exec();
}

