#ifndef TASKPRIORITYWIDGET_H
#define TASKPRIORITYWIDGET_H

#include "taskwidget.h"

class TaskPriorityWidget : public TaskWidget {
	Q_OBJECT
public:

	TaskPriorityWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QStringList& taskInfo, QWidget* parent =nullptr);
	TaskPriorityWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QString& taskName, QWidget* parent =nullptr);

};

#endif // TASKPRIORITYWIDGET_H
