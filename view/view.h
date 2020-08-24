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

#include "taskholder.h"
#include "taskwidget.h"
#include "projectpreview.h"
#include "projectview.h"
#include "controller/controller.h"

class View : public QMainWindow {
	Q_OBJECT

	Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	TaskWidget* t;
	QTabWidget* _projects;

	void setup();
	void openProject();
public:
	View(Controller* controller =nullptr, QWidget* parent =nullptr);
	void addMainLayout();
	void addList();
	void addMenu();
	void addToolBar();
	void addStatusBar();

signals:
	void appStart();
	void openProject(QString);

public slots:
	void fetchExistingProjects(QStringList);
};

#endif // VIEW_H
