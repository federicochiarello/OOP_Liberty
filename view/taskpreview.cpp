#include "taskpreview.h"

void TaskPreview::setup() {
	setContextMenuPolicy(Qt::CustomContextMenu);
//	setStyleSheet("TaskPreview { background: rgb(150, 255, 140); selection-background-color: rgb(233, 99, 0); }");

	_actions->addAction(_moveLeft);
	_actions->addAction(_moveRight);
	_actions->addAction(_duplicate);
	_actions->addAction(_delete);

}

void TaskPreview::connects() {

	connect(this, SIGNAL(getTaskName(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onGetTaskName(const unsigned short, const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTaskName(const unsigned short, const QString&)),
			this, SLOT(fetchTaskName(const unsigned short, const QString&)));

	connect(this, SIGNAL(openTask(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onOpenTask(const unsigned short, const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTaskInfo(const unsigned short, const QStringList&)),
			this, SLOT(fetchTaskInfo(const unsigned short, const QStringList&)));

	connect(this, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(customMenu(const QPoint&)));

	connect(_moveLeft, SIGNAL(triggered()),
			this, SLOT(onMoveLeft()));

	connect(_moveRight, SIGNAL(triggered()),
			this, SLOT(onMoveRight()));

	connect(this, SIGNAL(moveTask(const unsigned short, const unsigned short, const std::pair<unsigned short, TaskType>&, const Direction&)),
			_controller, SLOT(onMoveTask(const unsigned short, const unsigned short, const std::pair<unsigned short, TaskType>&, const Direction&)));

	connect(this, SIGNAL(editingFinished()), SLOT(onTaskNameChanged()));

	connect(this, SIGNAL(taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)),
			_controller, SLOT(onTaskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)));

	connect(_controller, SIGNAL(updateTaskPreviewName(const unsigned short, const QString&)),
			this, SLOT(setName(const unsigned short, const QString&)));

	connect(_controller, SIGNAL(moveTask(const unsigned short)),
			this, SLOT(onMoveTask(const unsigned short)));

	connect(_delete, SIGNAL(triggered()),
			this, SLOT(onDeleteTask()));

	connect(this, SIGNAL(deleteTask(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onDeleteTask(const unsigned short, const unsigned short, const unsigned short)));

	connect(_duplicate, SIGNAL(triggered()),
			this, SLOT(onDuplicateTask()));

	connect(this, SIGNAL(duplicateTask(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onDuplicateTask(const unsigned short, const unsigned short, const unsigned short)));
}

TaskPreview::TaskPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget *parent) :
	QLineEdit(parent),
	_id(id),
	_listId(listId),
	_projectId(projectId),
	_controller(controller),
	_task(nullptr),
	_actions(new QMenu(this)),
	_moveLeft(new QAction(tr("Sposta a sinistra"), _actions)),
	_moveRight(new QAction(tr("Sposta a destra"), _actions)),
	_duplicate(new QAction(tr("Duplica task"), _actions)),
	_delete(new QAction(tr("Elimina"), _actions)) {

	setup();
	connects();

	emit getTaskName(_projectId, _listId, _id);
}

unsigned short TaskPreview::getId() const {
	return _id;
}

void TaskPreview::mouseDoubleClickEvent(QMouseEvent*) {
	emit taskNameChanged(_projectId, _listId, _id, text());
	emit openTask(_projectId, _listId, _id);
}

void TaskPreview::fetchTaskName(const unsigned short taskId, const QString& taskName) {
	if (_id == taskId) {
		setText(taskName);
	}
}

void TaskPreview::fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo) {
	if (taskId == _id) {
		_task = new TaskWidget(taskId, _listId, _projectId, _controller, taskInfo);
		_task->show();
	}
}

void TaskPreview::customMenu(const QPoint& position) {

	_actions->popup(QWidget::mapToGlobal(position));
}

void TaskPreview::onMoveLeft() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK), LEFT);
}

void TaskPreview::onMoveRight() {
	emit moveTask(_projectId, _listId, std::pair<unsigned short, TaskType>(_id, TASK), RIGHT);
}

void TaskPreview::onTaskNameChanged() {
	emit taskNameChanged(_projectId, _listId, _id, text());
}

void TaskPreview::setName(const unsigned short taskId, const QString &newTaskName) {
	if (taskId == _id) {
		setText(newTaskName);
	}
}

void TaskPreview::onMoveTask(const unsigned short taskId) {
	if (taskId == _id) {
		disconnect(this, SIGNAL(taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)),
					_controller, SLOT(onTaskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)));
	}
}

void TaskPreview::onDeleteTask() {
	emit deleteTask(_projectId, _listId, _id);
}

void TaskPreview::onDuplicateTask() {
	emit duplicateTask(_projectId, _listId, _id);
}
