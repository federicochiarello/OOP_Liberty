#include "view.h"



void View::setup() {

	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	_centralWidget->setTabsClosable(true);
	createMenus();
	createToolBar();
}

void View::createActions() {

	_newProject = new QAction(tr("&New project"), _file);
	_newProject->setShortcut(QKeySequence::New);
	_newProject->setStatusTip(tr("Create new project"));


	_openProject = new QAction(tr("&Open project"), _file);
	_openProject->setShortcut(QKeySequence::Open);
	_openProject->setStatusTip(tr("Open existing project"));

	_saveProject = new QAction(tr("Salva"), _file);
	_saveProject->setShortcut(QKeySequence::Save);
	_saveProject->setStatusTip(tr("Salva progetto corrente"));


	_saveAllProjects = new QAction(tr("Salva tutti"), _file);
	_saveAllProjects->setStatusTip(tr("Salva tutti i progetti aperti"));


	_importProject = new QAction(tr("Import project"), _file);
	_importProject->setStatusTip(tr("Import existing project from file"));

	_exportProject = new QAction(tr("Export project"), _file);
	_exportProject->setStatusTip(tr("Export project file to directory"));

}

void View::createMenus() {
	createActions();

	_file->addAction(_newProject);
	_file->addAction(_openProject);
	_file->addAction(_saveProject);
	_file->addAction(_saveAllProjects);

	_menuBar->addMenu(_file);
}

void View::createToolBar() {

	_toolBar->setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	_toolButtonNew->setIcon(QIcon(":/icons/new_icon.png"));
	_toolButtonOpen->setIcon(QIcon(":/icons/open_icon.png"));
	_toolButtonSave->setIcon(QIcon(":/icons/save_icon.png"));
	_toolButtonExport->setIcon(QIcon(":/icons/export_icon.png"));

	_toolBar->addWidget(_toolButtonNew);
	_toolBar->addWidget(_toolButtonOpen);
	_toolBar->addWidget(_toolButtonSave);
	_toolBar->addWidget(_toolButtonExport);

	addToolBar(_toolBar);
}

void View::connects() {
	connect(this, SIGNAL(appStart()),
			this, SIGNAL(getStartingWidget()));

	connect(this, SIGNAL(appStart()),
			_controller, SLOT(onAppStart()));

	connect(this, SIGNAL(getProjectsDir()),
			_controller, SLOT(onGetProjectsDir()));

	connect(_centralWidget, SIGNAL(tabCloseRequested(int)),
			this, SLOT(onCloseTab(int)));

	connect(_controller, SIGNAL(sendProjectsDir(const QDir&)),
			this, SLOT(fetchProjectsDir(const QDir&)));

	connect(_controller, SIGNAL(sendExistingProjects(const QStringList&)),
			this, SLOT(fetchExistingProjects(const QStringList&)));

	connect(_controller, SIGNAL(sendProjectInfo(std::pair<unsigned short, QString>)),
			this, SLOT(fetchProjectInfo(std::pair<unsigned short, QString>)));

	connect(_newProject, SIGNAL(triggered()),
			this, SLOT(onNewProject()));

	connect(_toolButtonNew, SIGNAL(clicked()),
			this, SLOT(onNewProject()));

	connect(_toolButtonSave, SIGNAL(clicked()),
			_controller, SLOT(onSaveProject()));

	connect(_toolButtonOpen, SIGNAL(clicked()),
			this, SLOT(onOpenProject()));

	connect(_toolButtonExport, SIGNAL(clicked()),
			this, SLOT(onExportProject()));

	connect(_openProject, SIGNAL(triggered()),
			this, SLOT(onOpenProject()));

	connect(_saveProject, SIGNAL(triggered()),
			_controller, SLOT(onSaveProject()));

	connect(_saveAllProjects, SIGNAL(triggered()),
			_controller, SLOT(onSaveAllProjects()));

	connect(_importProject, SIGNAL(triggered()),
			this, SLOT(onImportProject()));

	connect(_exportProject, SIGNAL(triggered()),
			this, SLOT(onExportProject()));

	connect(this, SIGNAL(newProjectInfo(const QString&)),
			_controller, SLOT(onNewProject(const QString&)));

	connect(this, SIGNAL(openProject(const QString&)),
			_controller, SLOT(onOpenProject(const QString&)));

	connect(this, SIGNAL(importProject(const QString&)),
			_controller, SLOT(onImportProject(const QString&)));
}


View::View(const Controller* controller,QWidget* parent) :
	QMainWindow(parent),
	_controller(controller),
	_windowLayout(new QVBoxLayout()),
	_centralWidget(new QTabWidget()),
	_menuBar(new QMenuBar(this)),
	_file(new QMenu(tr("&File"), _menuBar)),
	_edit(new QMenu(tr("&Edit"), _menuBar)),
	_toolBar(new QToolBar(this)),
	_toolButtonNew(new QToolButton(_toolBar)),
	_toolButtonOpen(new QToolButton(_toolBar)),
	_toolButtonSave(new QToolButton(_toolBar)),
	_toolButtonExport(new QToolButton(_toolBar)) {

	setup();
	connects();

	emit appStart();
}

void View::onCloseTab(int index) {
	_centralWidget->removeTab(index);
}

void View::fetchProjectsDir(const QDir &projectsDir) {
	_projectsDir = projectsDir;
}

void View::fetchExistingProjects(const QStringList& projects) {
	QWidget* startingWidget = new QWidget(this);
	QVBoxLayout* startingWidgetLayout = new QVBoxLayout();

	for (int i=1; i<projects.size(); i++) {
		ProjectPreview* tmp = new ProjectPreview(_controller, projects.at(i), projects.at(0), startingWidget);
		startingWidgetLayout->addWidget(tmp);

	}

	startingWidget->setLayout(startingWidgetLayout);
	_centralWidget->addTab(startingWidget, tr("startingWidget"));
	setCentralWidget(_centralWidget);
}

void View::fetchProjectInfo(std::pair<unsigned short, QString> projectInfo) {

	ProjectView* project = new ProjectView(projectInfo, _controller, _centralWidget);
	if (_centralWidget) { // vi sono già dei progetti aperti
		_centralWidget->addTab(project, projectInfo.second);
	} else { // non vi sono progetti aperti, bisogna creare il QTabWidget che conterrá i progetti
		setCentralWidget(new QTabWidget(this));
		_centralWidget->addTab(project, projectInfo.second);
		project->setParent(_centralWidget);
	}
	_centralWidget->setCurrentWidget(project);

}

void View::onNewProject() {
	NewProjectDialog* project = new NewProjectDialog(_controller, this);
	project->show();
}

void View::onOpenProject() {
	if (_projectsDir == QDir::currentPath()) { //_projectsDir non inizializzata
		emit getProjectsDir();
	}
	emit openProject(QFileDialog::getOpenFileName(this, tr("Apri progetto"), _projectsDir.absolutePath(), tr("Projects(*.json)")));
}

void View::onImportProject() {
	emit importProject(QFileDialog::getOpenFileName(this, tr("Importa progetto"), QDir::homePath(), tr("Projects(*.json)")));
}

void View::onExportProject() {

}

void View::getNewProjectName(const QString& projectName) {
	emit newProjectInfo(projectName);
}

