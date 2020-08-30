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

	connect(this, SIGNAL(appStart()), _controller, SLOT(getExistingProjects()));
	connect(this, SIGNAL(openProject(const QString)), _controller, SLOT(openProject(const QString)));

	connect(_controller, SIGNAL(sendExistingProjects(const QStringList&)), this, SLOT(fetchExistingProjects(const QStringList&)));
	connect(_controller, SIGNAL(sendProjectInfo(const std::pair<unsigned short, QString>&)), this, SLOT(fetchProjectInfo(const std::pair<unsigned short, QString>&)));
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

void View::fetchExistingProjects(const QStringList& projects) {
	QWidget* startCentralWidget = new QWidget(this);
	QVBoxLayout* startCentralWidgetLayout = new QVBoxLayout();

	for (int i=1; i<projects.size(); i++) {
		ProjectPreview* tmp = new ProjectPreview(projects.at(i), projects.at(0), startCentralWidget);
		startCentralWidgetLayout->addWidget(tmp);
		connect(tmp, SIGNAL(openProject(const QString)), this, SIGNAL(openProject(const QString)));
	}

	startCentralWidget->setLayout(startCentralWidgetLayout);
	setCentralWidget(startCentralWidget);
}

void View::fetchProjectInfo(const std::pair<unsigned short, QString>& projectInfo) {


	QTabWidget* widget = dynamic_cast<QTabWidget*>(centralWidget());
	ProjectView* project = new ProjectView(projectInfo, widget);
	if (widget) { // vi sono già dei progetti aperti
		widget->addTab(project, projectInfo.second);
	} else { // non vi sono progetti aperti, bisogna creare il QTabWidget che conterrá i progetti
		setCentralWidget(new QTabWidget(this));
		widget->addTab(project, projectInfo.second);
		project->setParent(centralWidget());
	}

//	Creazione liste
	connect(project, SIGNAL(getLists(const unsigned short)),
			_controller, SLOT(onGetLists(const unsigned short)));

	connect(_controller, SIGNAL(sendListsIds(const unsigned short, std::vector<const unsigned short>)),
			project, SLOT(fetchListsIds(const unsigned short, std::vector<const unsigned short>)));

	connect(project, SIGNAL(getListName(const unsigned short, const unsigned short)),
			_controller, SLOT(onGetListName(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendListNqme(const unsigned short, const unsigned short, const QString&)),
			project, SLOT(fetchListName(const unsigned short, const unsigned short, const QString&)));

//	Creazione tasks
	connect(project, SIGNAL(getTasksIds(const unsigned short, const unsigned short)),
			_controller, SLOT(onGetTasksIds(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTasksIds(const unsigned short, const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)),
			project, SLOT(onSendTasksIds(const unsigned short, const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)));

	emit project->getLists(project->getId());
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
