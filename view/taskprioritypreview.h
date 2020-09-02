#ifndef TASKPRIORITYPREVIEW_H
#define TASKPRIORITYPREVIEW_H

#include "taskpreview.h"
#include "taskprioritywidget.h"

class TaskPriorityPreview : public TaskPreview {
	Q_OBJECT
public:

	TaskPriorityPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);

public slots:

	void fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) override;
	void onMoveLeft() override;
	void onMoveRight() override;
};

#endif // TASKPRIORITYPREVIEW_H
