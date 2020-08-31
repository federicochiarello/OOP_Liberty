#ifndef TASKPRIORITYCONTAINERPREVIEW_H
#define TASKPRIORITYCONTAINERPREVIEW_H

#include "taskpreview.h"
#include "taskprioritycontainerwidget.h"

class TaskPriorityContainerPreview : public TaskPreview {
	Q_OBJECT
public:

	TaskPriorityContainerPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);

signals:

public slots:
	void fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) override;

};

#endif // TASKPRIORITYCONTAINERPREVIEW_H
