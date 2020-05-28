#include "view.h"

View::View(Controller* controller,QWidget* parent) : QWidget(parent), _controller(controller), _windowLayout(new QVBoxLayout()) {
	setup();
}

void View::addMainLayout() {
	_mainLayout = new QHBoxLayout(this);

	_windowLayout->addLayout(_mainLayout);
}

void View::addList() {
	TaskHolder* tH = new TaskHolder(this);
	_mainLayout->addWidget(tH);
}

void View::addMenu() {
	/* Declaration menus and actions*/

	QMenuBar* menuBar = new QMenuBar(this);
	QMenu* file = new QMenu(tr("File"), menuBar);
	QAction* newProject = new QAction(tr("New project"), file);
	QAction* openProject = new QAction(tr("Open project"), file);
	QAction* importProject = new QAction(tr("Import project"), file);

	QMenu* edit = new QMenu(tr("Edit"), menuBar);
	QAction* undo = new QAction(tr("Undo"), edit);
	QAction* redo = new QAction(tr("Redo"), edit);
	/* Connect actions */

	//connect(newProject, SIGNAL(triggered()), _controller, SLOT());
	//connect(openProject, SIGNAL(triggered()), _controller, SLOT());
	//connect(importProject, SIGNAL(triggered()), _controller, SLOT());
	//connect(openProject, SIGNAL(triggered()), _controller, SLOT());
	//connect(openProject, SIGNAL(triggered()), _controller, SLOT());

	//connect(undo, SIGNAL(triggered()), _controller, SLOT());
	//connect(redo, SIGNAL(triggered()), _controller, SLOT());

	/* Add actions to menus */

	file->addAction(newProject);
	file->addAction(openProject);
	file->addAction(importProject);

	edit->addAction(undo);
	edit->addAction(redo);

	/* Add menus to manuBar */
	menuBar->addMenu(file);

	/* Add menuBar to layout */
	_windowLayout->addWidget(menuBar);
}

void View::addToolBar() {
	/* Declaration of toolbar and toolbuttons */
	QToolBar* toolBar = new QToolBar(this);
	QToolButton* toolB1 = new QToolButton(toolBar);
	QToolButton* toolB2 = new QToolButton(toolBar);

	/* Set toolBar properties */
	toolBar->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	/* Add toolbuttons to toolbar */
	toolBar->addWidget(toolB1);
	toolBar->addWidget(toolB2);

	/* Add toolbar to layout */
	_windowLayout->addWidget(toolB1);
	_windowLayout->addWidget(toolB2);
}

void View::setup() {
	addMenu();
	addToolBar();
	addMainLayout();
	addList();
	setLayout(_windowLayout);
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}
