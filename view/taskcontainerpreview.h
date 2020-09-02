#ifndef TASKCONTAINERPREVIEW_H
#define TASKCONTAINERPREVIEW_H

#include "taskpreview.h"
#include "taskcontainerwidget.h"

class TaskContainerPreview : public TaskPreview {
	Q_OBJECT

public:
	TaskContainerPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget* parent = nullptr);
public slots:
	void fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo) override;
	void onMoveLeft() override;
	void onMoveRight() override;
};

#endif // TASKCONTAINERPREVIEW_H
