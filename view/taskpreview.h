#ifndef TASKPREVIEW_H
#define TASKPREVIEW_H

#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QLayout>
#include <QMouseEvent>

#include "controller/controller.h"

#include "textholder.h"
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
//	explicit TaskPreview(QString taskName, const unsigned short id, const Controller* controller, QWidget* parent = nullptr);

	unsigned short getId() const;
protected:

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;

	//virtual void mousePressEvent(QMouseEvent *event) override;
	//virtual void mouseMoveEvent(QMouseEvent *event) override;

signals:

	void getTaskName(const unsigned short, const unsigned short, const unsigned short);
	void openTask(const unsigned short, const unsigned short, const unsigned short);

	void moveTask(const unsigned short, const unsigned short, const std::pair<unsigned short, TaskType>&, const Direction&);

	void openTaskInfo(const unsigned short);
	void taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&);

public slots:

	void fetchTaskName(const unsigned short taskId, const QString& taskName);
	virtual void fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo);

	void customMenu(const QPoint& position);
	virtual void onMoveLeft();
	virtual void onMoveRight();

	void onTaskNameChanged();
	void setName(const unsigned short taskId, const QString& newTaskName);
};

#endif // TASKPREVIEW_H
