#ifndef TASKPREVIEW_H
#define TASKPREVIEW_H

#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QLayout>
#include <QMouseEvent>

#include "controller/controller.h"

#include "taskwidget.h"

class TaskPreview : public QLineEdit {
	Q_OBJECT

protected:
	const unsigned short _id;
	const unsigned short _listId;
	const unsigned short _projectId;
	const Controller* _controller;

	TaskWidget* _task;
	QMenu* _actions;
	QAction* _moveLeft;
	QAction* _moveRight;
	QAction* _duplicate;
	QAction* _delete;

	void setup();
	void connects();

public:

	TaskPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);

	unsigned short getId() const;

protected:

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

signals:

	void getTaskName(const unsigned short, const unsigned short, const unsigned short);
	void openTask(const unsigned short, const unsigned short, const unsigned short);
	void taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&);
	void moveTask(const unsigned short, const unsigned short, const std::pair<unsigned short, TaskType>&, const Direction&);
	void deleteTask(const unsigned short, const unsigned short, const unsigned short);
	void duplicateTask(const unsigned short, const unsigned short, const unsigned short);
	void openTaskInfo(const unsigned short);

public slots:

	void			customMenu(const QPoint& position);
	void			fetchTaskName(const unsigned short taskId, const QString& taskName);
	virtual void	fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo);
	void			onTaskNameChanged();
	void			setName(const unsigned short taskId, const QString& newTaskName);
	virtual void	onMoveLeft();
	virtual void	onMoveRight();
	void			onMoveTask(const unsigned short taskId);
	void			onDeleteTask();
	void			onDuplicateTask();


};

#endif // TASKPREVIEW_H
