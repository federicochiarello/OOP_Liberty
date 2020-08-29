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

class TasksListWidget : public QWidget {
	Q_OBJECT

	unsigned short _id;
	QVBoxLayout* _layout;
	std::string _name;
	TasksList* _list;

	void setup();

public:

	explicit TasksListWidget(QWidget* parent =nullptr);
	explicit TasksListWidget(std::string listName, QWidget* parent =nullptr);
	TasksListWidget(const unsigned short listId, QWidget* parent =nullptr);
	~TasksListWidget();

signals:

	void moveTaskForward(const unsigned short);
	void moveTaskBackward(const unsigned short);

public slots:

	//	void addTask();
};

#endif // TASKSLISTWIDGET_H
