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

#include <QDebug>

class View : public QMainWindow {
	Q_OBJECT

	const Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	QTabWidget* _centralWidget;

	void setup();
	void connects();
	void openProject();

public:

	explicit View(const Controller* controller =nullptr, QWidget* parent =nullptr);

	void addMainLayout();
	void addMenu();
	void addToolBar();
	void addStatusBar();

signals:

	void appStart();
	void getStartingWidget();
	void newProject();
//	void openProject(const QString); eliminato

public slots:

	void fetchExistingProjects(const QStringList&);
	void fetchProjectInfo(std::pair<unsigned short, QString> projectInfo);
};

#endif // VIEW_H
