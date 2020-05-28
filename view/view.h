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

#include "taskholder.h"
#include "taskwidget.h"

class Controller : public QObject {
	Q_OBJECT
	int c;
public:
	Controller() {}
};

class View : public QWidget {
	Q_OBJECT
public:
	View(Controller* controller, QWidget* parent =nullptr);
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

	void setup();
};

#endif // VIEW_H
