#include "taskprioritypreview.h"

TaskPriorityPreview::TaskPriorityPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, QWidget *parent) :
	TaskPreview(id, listId, projectId, controller, parent) {}

void TaskPriorityPreview::fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) {
	if (taskId == _id) {
		_task = new TaskPriorityWidget(_id, _listId, _projectId, _controller, taskInfo, this);
	}
}
