#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QLayout>
#include <QMenuBar>
#include <QPushButton>
#include <QToolBar>
#include <QToolButton>
#include <QDesktopWidget>
#include <QTabWidget>
#include <QDialogButtonBox>

#include "projectpreview.h"
#include "projectview.h"
#include "newprojectdialog.h"

#include "controller/controller.h"

#include <QDebug>

class View : public QMainWindow {
	Q_OBJECT

	const Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	QTabWidget* _centralWidget;

	QMenu* _file;
	QMenu* _edit;

	QAction* _newProject;
	QAction* _openProject;

	void setup();
	void connects();
	void openProject();

	void createActions();
	void createMenus();

public:

	explicit View(const Controller* controller =nullptr, QWidget* parent =nullptr);

	void addMainLayout();
	void addMenu();
	void addToolBar();
	void addStatusBar();

signals:

	void appStart();
	void getStartingWidget();
	void newProjectInfo(const QString&);
//	void openProject(const QString); eliminato

public slots:

	void fetchExistingProjects(const QStringList&);
	void fetchProjectInfo(std::pair<unsigned short, QString> projectInfo);
	void newProject();
	void getNewProjectName(const QString& projectName);
};

#endif // VIEW_H
