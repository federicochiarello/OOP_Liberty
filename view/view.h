#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenuBar>
#include <QPushButton>

class Controller{
	int c;
public:
	Controller() {}
};

class View : public QWidget {
	Q_OBJECT
public:
	View(Controller* controller, QWidget* parent =nullptr);
	void addMenu();
	void addControlStrip();
private:
	Controller* _controller;
	QVBoxLayout _windowLayout;
	QHBoxLayout _mainLayout;
};

#endif // VIEW_H
