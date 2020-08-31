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

	void connects();

public:

	TaskPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);
//	explicit TaskPreview(QString taskName, const unsigned short id, const Controller* controller, QWidget* parent = nullptr);

protected:

	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;

	//virtual void mousePressEvent(QMouseEvent *event) override;
	//virtual void mouseMoveEvent(QMouseEvent *event) override;

signals:

	void getTaskName(const unsigned short, const unsigned short, const unsigned short);
	void openTask(const unsigned short);

	void openTaskInfo(unsigned short);
	void changedTaskName(unsigned short, std::string);

public slots:

	void fetchTaskName(const unsigned short taskId, const QString& taskName);
	virtual void fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo);

};

#endif // TASKPREVIEW_H
