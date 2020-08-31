#ifndef TASKPRIORITYCONTAINERWIDGET_H
#define TASKPRIORITYCONTAINERWIDGET_H

#include "taskwidget.h"

#define TPCW TaskPriorityContainerWidget

class TaskPriorityContainerWidget : public TaskWidget {
	Q_OBJECT
public:
	TaskPriorityContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QStringList& taskInfo, QWidget* parent =nullptr);
	TaskPriorityContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QString& taskName, QWidget* parent =nullptr);
};

#endif // TASKPRIORITYCONTAINERWIDGET_H
