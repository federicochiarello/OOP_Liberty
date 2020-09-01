#include "view.h"

void View::connects() {
	connect(this, SIGNAL(appStart()),
			this, SIGNAL(getStartingWidget()));

	connect(this, SIGNAL(appStart()), // cambiare appStart() con getStartingWidget() e cambiare in controller
			_controller, SLOT(onAppStart()));

	connect(_controller, SIGNAL(sendExistingProjects(const QStringList&)),
			this, SLOT(fetchExistingProjects(const QStringList&)));

	connect(_controller, SIGNAL(sendProjectInfo(std::pair<unsigned short, QString>)),
			this, SLOT(fetchProjectInfo(std::pair<unsigned short, QString>)));

	connect(this, SIGNAL(newProjectInfo(const QString&)),
			_controller, SLOT(onNewProject(const QString&)));
}

void View::createActions() {
	_newProject = new QAction(tr("&New project"), this);
	_newProject->setShortcut(QKeySequence::New);
	_newProject->setStatusTip(tr("Create new project"));
	connect(_newProject, SIGNAL(triggered()),
			this, SLOT(newProject()));
}

void View::createMenus() {
	createActions();

	_file = menuBar()->addMenu(tr("&File"));
	_file->addAction(_newProject);

	_edit = menuBar()->addMenu(tr("&Edit"));
}

View::View(const Controller* controller,QWidget* parent) :
	QMainWindow(parent),
	_controller(controller),
	_windowLayout(new QVBoxLayout()),
	_centralWidget(new QTabWidget(this)) {

	setup();
	connects();

	qDebug() << "Start";
	emit appStart();
}

void View::addMainLayout() {
	_mainLayout = new QHBoxLayout(this);

	_windowLayout->addLayout(_mainLayout);
}

//void View::addList() {
//	TaskHolder* taskHolder = new TaskHolder(this);
//	_mainLayout->addWidget(taskHolder);
//}

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
	QWidget* startingWidget = new QWidget(this);
	QVBoxLayout* startingWidgetLayout = new QVBoxLayout();

	for (int i=1; i<projects.size(); i++) {
		ProjectPreview* tmp = new ProjectPreview(_controller, projects.at(i), projects.at(0), startingWidget);
		startingWidgetLayout->addWidget(tmp);
//		connect(tmp, SIGNAL(openProject(const QString)), this, SIGNAL(openProject(const QString))); eliminato
	}

	startingWidget->setLayout(startingWidgetLayout);
	_centralWidget->addTab(startingWidget, tr("startingWidget"));
	setCentralWidget(_centralWidget);
}

void View::fetchProjectInfo(std::pair<unsigned short, QString> projectInfo) {

//	QTabWidget* widget = dynamic_cast<QTabWidget*>(centralWidget());
	qDebug() << "Info passed: " <<projectInfo.first << " " << projectInfo.second;
	ProjectView* project = new ProjectView(projectInfo, _controller, _centralWidget);
	if (_centralWidget) { // vi sono già dei progetti aperti
		_centralWidget->addTab(project, projectInfo.second);
	} else { // non vi sono progetti aperti, bisogna creare il QTabWidget che conterrá i progetti
		setCentralWidget(new QTabWidget(this));
		_centralWidget->addTab(project, projectInfo.second);
		project->setParent(_centralWidget);
	}
	_centralWidget->setCurrentWidget(project);

//	Creazione liste
//	connect(project, SIGNAL(getLists(const unsigned short)),
//			_controller, SLOT(onGetLists(const unsigned short))); elminato

//	connect(_controller, SIGNAL(sendListsIds(const unsigned short, std::vector<unsigned short>)),
//			project, SLOT(fetchListsIds(const unsigned short, std::vector<unsigned short>))); eliminato

//	connect(project, SIGNAL(getListName(const unsigned short, const unsigned short)),
//			_controller, SLOT(onGetListName(const unsigned short, const unsigned short)));

//	connect(_controller, SIGNAL(sendListNqme(const unsigned short, const unsigned short, const QString&)),
//			project, SLOT(fetchListName(const unsigned short, const unsigned short, const QString&)));

////	Creazione tasks
//	connect(project, SIGNAL(getTasksIds(const unsigned short, const unsigned short)),
//			_controller, SLOT(onGetTasksIds(const unsigned short, const unsigned short)));

//	connect(_controller, SIGNAL(sendTasksIds(const unsigned short, const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)),
//			project, SLOT(onSendTasksIds(const unsigned short, const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>)));

	//	emit project->getLists(project->getId());
}

void View::newProject() {
	NewProjectDialog* project = new NewProjectDialog(_controller, this);
	project->show();
}

void View::getNewProjectName(const QString& projectName) {
	qDebug() << projectName;
//	emit newProjectInfo(projectName);
}

void View::setup() {

	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	// Menu

	// Declaration menus and actions

	createMenus();
//	QMenuBar* menuBar = new QMenuBar(this);
//	QMenu* fileMenu = new QMenu(tr("File"), menuBar);
//	QAction* newProAct = new QAction(tr("New project"), fileMenu);
//	QAction* openProAct = new QAction(tr("Open project"), fileMenu);
//	QAction* importProAct = new QAction(tr("Import project"), fileMenu);

//	QMenu* editMenu = new QMenu(tr("Edit"), menuBar);
//	QAction* undoAct = new QAction(tr("Undo"), editMenu);
//	QAction* redoAct = new QAction(tr("Redo"), editMenu);

	// Set shortcut

//	newProAct->setShortcut(QKeySequence::New);


//	// Set status tip

//	newProAct->setStatusTip(tr(""));
//	openProAct->setStatusTip(tr(""));
//	importProAct->setStatusTip(tr(""));

//	undoAct->setStatusTip(tr(""));
//	redoAct->setStatusTip(tr(""));

//	// Connect actions


//	connect(newProAct, SIGNAL(triggered()),
//			this, SLOT(newProject()));
//	connect(openProAct, SIGNAL(triggered()), _controller, SLOT());
//	connect(importProAct, SIGNAL(triggered()), _controller, SLOT());

//	connect(undoAct, SIGNAL(triggered()), _controller, SLOT());
//	connect(redoAct, SIGNAL(triggered()), _controller, SLOT());

//	connect(this, SIGNAL(openProject(const QString)), _controller, SLOT(openProject(const QString))); eliminato

	// Add actions to menu

//	fileMenu->addAction(newProAct);
//	fileMenu->addAction(openProAct);
//	fileMenu->addAction(importProAct);

//	editMenu->addAction(undoAct);
//	editMenu->addAction(redoAct);

	// Add menus to menuBar


//	menuBar->addMenu(fileMenu);
//	menuBar->addMenu(editMenu);

	// Toolbar

	// DockWidget

	// Central widget
	setCentralWidget(_centralWidget);
}
