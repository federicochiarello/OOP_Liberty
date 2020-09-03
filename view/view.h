#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QLayout>
#include <QMenuBar>
#include <QToolBar>
#include <QToolButton>
#include <QTabWidget>
#include <QFileDialog>
#include <QDialogButtonBox>

#include "projectpreview.h"
#include "projectview.h"
#include "newprojectdialog.h"

#include "controller/controller.h"

class View : public QMainWindow {
	Q_OBJECT

	const Controller* _controller;
	QDir _projectsDir;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	QTabWidget* _centralWidget;

	QMenuBar* _menuBar;
	QMenu* _file;
	QMenu* _edit;

	QAction* _newProject;
	QAction* _openProject;
	QAction* _saveProject;
	QAction* _saveAllProjects;
	QAction* _importProject;
	QAction* _exportProject;

	QToolBar* _toolBar;
	QToolButton* _toolButtonNew;
	QToolButton* _toolButtonOpen;
	QToolButton* _toolButtonSave;
	QToolButton* _toolButtonExport;

	void setup();
	void connects();

	void createActions();
	void createMenus();
	void createToolBar();

public:

	explicit View(const Controller* controller =nullptr, QWidget* parent =nullptr);

signals:

	void appStart();
	void getProjectsDir();
	void getStartingWidget();
	void importProject(const QString&);
	void exportProject(const QString&);
	void newProjectInfo(const QString&);
	void openProject(const QString&);

private slots:

	void onCloseTab(int index);

public slots:

	void fetchProjectsDir(const QDir& projectsDir);
	void fetchExistingProjects(const QStringList&);
	void fetchProjectInfo(std::pair<unsigned short, QString> projectInfo);
	void onNewProject();
	void onOpenProject();
	void onImportProject();
	void onExportProject();
	void getNewProjectName(const QString& projectName);
};

#endif // VIEW_H
