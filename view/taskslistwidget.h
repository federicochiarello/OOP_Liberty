#ifndef TASKSLISTWIDGET_H
#define TASKSLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>

#include "taskslist.h"
#include <QDebug>

#define TLW TasksListWidget

class TasksListWidget : public QWidget {
	Q_OBJECT

	QVBoxLayout* _layout;
	std::string _name;
	TasksList* _list;

	void setup();
public:
	explicit TasksListWidget(QWidget* parent =nullptr);
	explicit TasksListWidget(std::string listName, QWidget* parent =nullptr);
	~TasksListWidget();

public slots:
//	void addTask();
signals:

};

#endif // TASKSLISTWIDGET_H
