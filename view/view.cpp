#include "view.h"

View::View(QWidget* parent) : QWidget(parent), mainLayout(new QVBoxLayout(this)) {
	createMenu();
}

void View::createMenu() {
	QMenuBar* menuBar = new QMenuBar(this);
	QMenu* file = new QMenu(tr("File"), menuBar);
	QAction* newFile = new QAction(tr("New file"), file);
	file->addAction(newFile);
	menuBar->addMenu(file);
	mainLayout->addWidget(menuBar);
}
