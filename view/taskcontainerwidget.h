#ifndef TASKCONTAINERWIDGET_H
#define TASKCONTAINERWIDGET_H

#include "taskwidget.h"


class TaskContainerWidget : public TaskWidget {
	Q_OBJECT
public:

	TaskContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QStringList& taskInfo, QWidget* parent =nullptr);
	TaskContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QString& taskName, QWidget* parent =nullptr);

signals:
	void addSubTask(unsigned short);

public slots:

};

#endif // TASKCONTAINERWIDGET_H
