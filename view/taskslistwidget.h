#ifndef TASKSLISTWIDGET_H
#define TASKSLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>

#include "src/globalenums.h"

#include "controller/controller.h"

#include "taskslist.h"

class TasksListWidget : public QWidget {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _projectId;
	const Controller* _controller;

	QLineEdit* _title;
	QVBoxLayout* _layout;
	std::string _name;
	TasksList* _list;
//	Controller* _controller;

	void setup();
	void connects();

public:

//	explicit TasksListWidget(QWidget* parent =nullptr);
//	explicit TasksListWidget(QString listName, QWidget* parent =nullptr);
	TasksListWidget(const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent =nullptr);
	~TasksListWidget();

	unsigned short getId() const;

signals:

	void getListName(const unsigned short, const unsigned short);
	void getTasksIds(const unsigned short);
	void getTaskName(const unsigned short, const unsigned short);
	void sendTaskName(const unsigned short, const QString&);

	void moveTaskForward(const unsigned short);
	void moveTaskBackward(const unsigned short);

public slots:

	void fetchListName(const unsigned short projectId, const unsigned short listId, const QString& listName);
	void fetchTasksIds(const unsigned short projectId, const unsigned short listId, const std::vector<std::pair<const unsigned short, const TaskType&>> tasksIds);

	void onGetTaskName(const unsigned short taskId);
	void onSendTaskName(const unsigned short listId, const unsigned short taskId, const QString& taskName);
	//	void addTask();
};

#endif // TASKSLISTWIDGET_H
