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

#include "projectpreview.h"
#include "projectview.h"
#include "controller/controller.h"

class View : public QMainWindow {
	Q_OBJECT

	Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	QTabWidget* _projects;

	void setup();
	void connects();
	void openProject();

public:

	explicit View(Controller* controller =nullptr, QWidget* parent =nullptr);

	void addMainLayout();
	void addList();
	void addMenu();
	void addToolBar();
	void addStatusBar();

signals:

	void appStart();
//	void openProject(const QString); eliminato

public slots:

	void fetchExistingProjects(const QStringList&);
	void fetchProjectInfo(const std::pair<const unsigned short, const QString&>& projectInfo);
};

#endif // VIEW_H
