#include "view.h"

View::View(Controller* controller,QWidget* parent) : QWidget(parent), _controller(controller) {
	addMenu();
	addControlStrip();
}

void View::addMenu() {
	QMenuBar* menuBar = new QMenuBar(this);
	QMenu* file = new QMenu(tr("File"), menuBar);
	QAction* newFile = new QAction(tr("New file"), file);
	file->addAction(newFile);
	menuBar->addMenu(file);
	_windowLayout.addWidget(menuBar);
}

void View::addControlStrip() {
	QHBoxLayout* controlStrip = new QHBoxLayout(this);
	for (int i=0; i<5; i++) {
		QPushButton* button = new QPushButton(this);
		controlStrip->addWidget(button);
	}
	_windowLayout.addLayout(controlStrip);
}
