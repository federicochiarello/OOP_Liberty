#include "taskcontainerpreview.h"

TaskContainerPreview::TaskContainerPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, QWidget *parent) :
	TaskPreview(id, listId, projectId, controller, parent) {
	setStyleSheet("TaskContainerPreview { background: rgb(255, 165, 0); selection-background-color: rgb(0, 165, 255); }");
}

void TaskContainerPreview::fetchTaskInfo(const unsigned short taskId, const QStringList &taskInfo) {
	if (taskId == _id) {
		_task = new TaskContainerWidget(taskId, _listId, _projectId, _controller, taskInfo);
		_task->show();
	}
}

void TaskContainerPreview::onMoveLeft() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_CONTAINER), LEFT);
}

void TaskContainerPreview::onMoveRight() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK_CONTAINER), RIGHT);
}
