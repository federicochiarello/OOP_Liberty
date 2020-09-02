#include "taskslist.h"

void TasksList::setup() {

	//	setDragEnabled(true);
		setAcceptDrops(true);
		setWidgetResizable(true);

		_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		_widget->setLayout(_layout);
		_widget->autoFillBackground();
		setWidget(_widget);

}

void TasksList::connects() {
	connect(this, SIGNAL(newTask(const unsigned short, const unsigned short)),
			_controller, SLOT(onNewTask(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendNewTasksList(const unsigned short, const std::pair<unsigned short, TaskType>&)),
			this, SLOT(fetchNewTasksList(const unsigned short, const std::pair<unsigned short, TaskType>&)));

	connect(_controller, SIGNAL(sendDeleteTaskFromList(const unsigned short, const unsigned short)),
			this, SLOT(fetchDeleteTaskFromList(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(removeTask(const unsigned short, const unsigned short)),
			this, SLOT(fetchDeleteTaskFromList(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(duplicatedTask(const unsigned short, const unsigned short)),
			this, SLOT());
}

void TasksList::removeTask(const unsigned short taskId) {
	auto children = _layout->children();
	for (auto i = 0; i < _layout->count(); i++) {
		TaskPreview* tmp = dynamic_cast<TaskPreview*>(_layout->itemAt(i)->widget());
		if (tmp && (tmp->getId() == taskId)) {
			_layout->removeWidget(tmp);
			delete tmp;
			setWidget(_widget);
		}
	}
}

TasksList::TasksList(const unsigned short id, const unsigned short projectId, const Controller* controller, QWidget *parent) :
	QScrollArea(parent),
	_id(id),
	_projectId(projectId),
	_controller(controller),
	_layout(new QVBoxLayout()),
	_widget(new QWidget(this)) {

	setup();
	connects();
}

void TasksList::addWidget(TaskPreview* task) {
	_layout->addWidget(task);
}

void TasksList::onNewTask() {
	qDebug() << "Richiesta nuovo task";
	emit newTask(_projectId, _id);
}

void TasksList::addTask(const std::pair<unsigned short, TaskType>& taskId) {
	TaskPreview* task;
	switch (taskId.second) {
		case TASK:
			task = new TaskPreview(taskId.first, _id, _projectId, _controller, this);
			break;
		case TASK_CONTAINER:
			task = new TaskContainerPreview(taskId.first, _id, _projectId, _controller, this);
			break;
		case TASK_PRIORITY:
			task = new TaskPriorityPreview(taskId.first, _id, _projectId, _controller, this);
			break;
		case TASK_PRIORITY_CONTAINER:
			task = new TaskPriorityContainerPreview(taskId.first, _id, _projectId, _controller, this);
			break;
		default:
			task = nullptr;
			break;
	}
	if (task) {
		addWidget(task);
		task->setFocus();
	}
}

void TasksList::fetchNewTasksList(const unsigned short newListId, const std::pair<unsigned short, TaskType>& taskId) {
	if (newListId == _id) {
		addTask(taskId);
	}
}

void TasksList::fetchDeleteTaskFromList(const unsigned short listId, const unsigned short taskId) {
	if (listId == _id) {
		removeTask(taskId);
	}
}
