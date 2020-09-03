#include "taskprioritypreview.h"

TaskPriorityPreview::TaskPriorityPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, QWidget *parent) :
	TaskPreview(id, listId, projectId, controller, parent) {
	setStyleSheet("TaskPriorityPreview { background: rgb(3, 192, 60); selection-background-color: rgb(200, 92, 3); }");
}

void TaskPriorityPreview::fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) {
	if (taskId == _id) {
		_task = new TaskPriorityWidget(_id, _listId, _projectId, _controller, taskInfo);
		_task->show();
	}
}

void TaskPriorityPreview::onMoveLeft() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_PRIORITY), LEFT);
}

void TaskPriorityPreview::onMoveRight() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_PRIORITY), RIGHT);
}
