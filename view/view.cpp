#include "view.h"

View::View(Controller* controller,QWidget* parent) : QMainWindow(parent), _controller(controller), _windowLayout(new QVBoxLayout()), _projects(new QTabWidget(this)) {
	// Menu

	// Declaration menus and actions

	QMenu* fileMenu = new QMenu(tr("File"), menuBar());
	QAction* newProAct = new QAction(tr("New project"), fileMenu);
	QAction* openProAct = new QAction(tr("Open project"), fileMenu);
	QAction* importProAct = new QAction(tr("Import project"), fileMenu);

	QMenu* editMenu = new QMenu(tr("Edit"), menuBar());
	QAction* undoAct = new QAction(tr("Undo"), editMenu);
	QAction* redoAct = new QAction(tr("Redo"), editMenu);

	// Set shortcut

	newProAct->setShortcut(QKeySequence::New);


	// Set status tip

	newProAct->setStatusTip(tr(""));
	openProAct->setStatusTip(tr(""));
	importProAct->setStatusTip(tr(""));

	undoAct->setStatusTip(tr(""));
	redoAct->setStatusTip(tr(""));

	// Connect actions

//	connect(newProAct, SIGNAL(triggered()), _controller, SLOT());
//	connect(openProAct, SIGNAL(triggered()), _controller, SLOT());
//	connect(importProAct, SIGNAL(triggered()), _controller, SLOT());

//	connect(undoAct, SIGNAL(triggered()), _controller, SLOT());
//	connect(redoAct, SIGNAL(triggered()), _controller, SLOT());

	// Add actions to menu

	fileMenu->addAction(newProAct);
	fileMenu->addAction(openProAct);
	fileMenu->addAction(importProAct);

	editMenu->addAction(undoAct);
	editMenu->addAction(redoAct);

	// Add menus to menuBar

	menuBar()->addMenu(fileMenu);
	menuBar()->addMenu(editMenu);

	// Toolbar

	// DockWidget

	// Central widget
//	setCentralWidget(new QTabWidget(this));

	emit appStart();
}

void View::addMainLayout() {
	_mainLayout = new QHBoxLayout(this);

	_windowLayout->addLayout(_mainLayout);
}

void View::addList() {
	TaskHolder* taskHolder = new TaskHolder(this);
	_mainLayout->addWidget(taskHolder);
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

void View::fetchExistingProjects(QStringList projects) {
	QWidget* startCentralWidget = new QWidget(this);
	QHBoxLayout* startCentralWidgetLayout = new QHBoxLayout();

	for (int i=1; i<=projects.size(); i++) {
		ProjectPreview* tmp = new ProjectPreview(projects.at(i), projects.at(0), startCentralWidget);
		startCentralWidgetLayout->addWidget(tmp);
		connect(tmp, SIGNAL(openProject(QString)), this, SIGNAL(openProject(QString)));
	}

	startCentralWidget->setLayout(startCentralWidgetLayout);
	setCentralWidget(startCentralWidget);
}

void View::setup() {
	//addMenu();
	addToolBar();
	//addMainLayout();
	addList();
	_windowLayout->addWidget(_projects);
	ProjectView* proj = new ProjectView(this);
	_projects->addTab(proj, tr("Titolo"));
	setLayout(_windowLayout);
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
}
