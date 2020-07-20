#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>
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

class View : public QWidget {
	Q_OBJECT
public:
	View(Controller* controller =nullptr, QWidget* parent =nullptr);
	void addMainLayout();
	void addList();
	void addMenu();
	void addToolBar();
	void addStatusBar();

private:
	Controller* _controller;
	QVBoxLayout* _windowLayout;
	QHBoxLayout* _mainLayout;
	TaskWidget* t;
	QTabWidget* _projects;

	void setup();
};

#endif // VIEW_H
