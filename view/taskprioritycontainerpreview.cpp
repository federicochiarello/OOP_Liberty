#include "taskprioritycontainerpreview.h"

TaskPriorityContainerPreview::TaskPriorityContainerPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, QWidget *parent) :
	TaskPreview(id, listId, projectId, controller, parent) {}

void TaskPriorityContainerPreview::fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) {
	if (taskId == _id) {
		_task = new TaskPriorityContainerWidget(_id, _listId, _projectId, _controller, taskInfo);
		_task->show();
	}
}

void TaskPriorityContainerPreview::onMoveLeft() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_PRIORITY_CONTAINER), LEFT);
}

void TaskPriorityContainerPreview::onMoveRight() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_PRIORITY_CONTAINER), RIGHT);
}
