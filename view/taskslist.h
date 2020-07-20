#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QLabel>
#include <QListView>
#include <QStringListModel>
#include <QLineEdit>

#include "taskwidget.h"
#include "tpreview.h"

#include <QDebug>

class TasksList : public QWidget {
	Q_OBJECT

	QVBoxLayout* _layout;
	std::string _name;
	QListView* _list;

	void setup();
public:
	TasksList(QWidget* parent =nullptr, std::string listName =std::string());

	operator QListView*() {return _list;}
public slots:
	void addTask();
};

#endif // TASKSLIST_H
