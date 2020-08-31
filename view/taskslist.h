#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QLayout>
#include <QScrollArea>
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>
#include <QLineEdit>

#include "src/globalenums.h"

#include "controller/controller.h"

#include "taskwidget.h"
#include "taskpreview.h"

class TasksList : public QScrollArea {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _projectId;
	const Controller* _controller;
	QVBoxLayout* _layout;
	QWidget* _widget;

public:
	explicit TasksList(const unsigned short id, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);

	void addWidget(QLineEdit* widget);
protected:
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

signals:

	void getTaskName(const unsigned short);

//	void newTask(unsigned short);
	void deleteTask(unsigned short);

public slots:

	void fetchTaskName(const unsigned short taskId, const QString& taskName);

	void addTask();
	void addTask(const std::pair<const unsigned short, const TaskType&> taskId);

};

class DragDrop : public QWidget {
	Q_OBJECT
public:
	explicit DragDrop(QWidget* parent =nullptr);

protected:
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

};

#endif // TASKSLIST_H
