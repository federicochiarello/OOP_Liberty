#include "taskcontainerpreview.h"

TaskContainerPreview::TaskContainerPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, QWidget *parent) :
	TaskPreview(id, listId, projectId, controller, parent) {}

void TaskContainerPreview::fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) {
	if (taskId == _id) {
		_task = new TaskContainerWidget(taskId, _listId, _projectId, _controller, taskInfo);
		_task->show();
	}
}
