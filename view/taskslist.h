#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QLayout>
#include <QScrollArea>
#include <QDropEvent>
#include <QLineEdit>

#include "src/globalenums.h"

#include "controller/controller.h"

#include "taskpreview.h"
#include "taskcontainerpreview.h"
#include "taskprioritypreview.h"
#include "taskprioritycontainerpreview.h"

class TasksList : public QScrollArea {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _projectId;
	const Controller* _controller;
	QVBoxLayout* _layout;
	QWidget* _widget;

	void setup();
	void connects();
	void removeTask(const unsigned short taskId);

public:
	explicit TasksList(const unsigned short id, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);

	void addWidget(TaskPreview* task);

signals:

	void getTaskName(const unsigned short);

	void newTask(const unsigned short, const unsigned short);
	void deleteTask(const unsigned short);

public slots:

//	void fetchTaskName(const unsigned short taskId, const QString& taskName);

	void onNewTask();
	void addTask(const std::pair<unsigned short, TaskType>& taskId);
	void fetchNewTasksList(const unsigned short newListId, const std::pair<unsigned short, TaskType>& taskId);
	void fetchDeleteTaskFromList(const unsigned short listId, const unsigned short taskId);

};

#endif // TASKSLIST_H
