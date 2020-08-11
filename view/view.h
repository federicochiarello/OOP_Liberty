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
#include "projectview.h"

class Controller;

class View : public QMainWindow {
	Q_OBJECT

	Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	TaskWidget* t;
	QTabWidget* _projects;

	void setup();

public:
	View(Controller* controller =nullptr, QWidget* parent =nullptr);
	void addMainLayout();
	void addList();
	void addMenu();
	void addToolBar();
	void addStatusBar();

signals:

public slots:
};

#endif // VIEW_H
