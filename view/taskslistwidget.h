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

#include <QDebug>

class TasksListWidget : public QWidget {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _projectId;
	const Controller* _controller;

	QVBoxLayout* _layout;
	QHBoxLayout* _header;

	QLineEdit* _title;
	QPushButton* _buttonActions;
	QMenu* _menu;
	QAction* _actionNewTask;
	QAction* _actionMoveListLeft;
	QAction* _actionMoveListRight;
	TasksList* _list;

	void setup();
	void connects();

public:

//	explicit TasksListWidget(QWidget* parent =nullptr);
//	explicit TasksListWidget(QString listName, QWidget* parent =nullptr);
	TasksListWidget(const unsigned short listId, const unsigned short projectId, const bool& isNew, const Controller* controller, QWidget* parent =nullptr);
	~TasksListWidget();

	unsigned short getId() const;

signals:

	void getListName(const unsigned short, const unsigned short);
	void getTasksIds(const unsigned short, const unsigned short);
	void getTaskName(const unsigned short, const unsigned short);
	void sendTaskName(const unsigned short, const QString&);
	void listNameChanged(const unsigned short, const unsigned short, const QString&);

	void moveList(const unsigned short, const unsigned short, const Direction&);

public slots:

	void fetchListName(const unsigned short listId, const QString& listName);
	void fetchTaskId(const unsigned short listId, const std::pair<unsigned short, TaskType>& taskId);
	void fetchTasksIds(const unsigned short listId, const std::vector<std::pair<unsigned short, TaskType>>& tasksIds);
	void onListNameChanged();
	void onMoveListLeft();
	void onMoveListRight();

//	void onGetTaskName(const unsigned short taskId);
//	void onSendTaskName(const unsigned short listId, const unsigned short taskId, const QString& taskName);
	//	void addTask();
};

#endif // TASKSLISTWIDGET_H
