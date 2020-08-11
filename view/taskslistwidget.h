#ifndef TASKSLISTWIDGET_H
#define TASKSLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>

#include "taskwidget.h"
#include "taskpreview.h"
#include <QDebug>

class TasksListWidget : public QWidget {
	Q_OBJECT

	QVBoxLayout* _layout;
	std::string _name;
	QScrollArea* _list;

	void setup();
public:
	TasksListWidget(std::string listName, QWidget* parent =nullptr);
	TasksListWidget(QWidget* parent =nullptr);
	~TasksListWidget();
	//operator QListView*() {return _list;}
public slots:
	void addTask();
};

#endif // TASKSLISTWIDGET_H
