#include "taskpreview.h"

void TaskPreview::connects() {

	connect(this, SIGNAL(getTaskName(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onGetTaskName(const unsigned short, const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTaskName(const unsigned short, const QString&)),
			this, SLOT(fetchTaskName(const unsigned short, const QString&)));

	connect(this, SIGNAL(openTask(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onOpenTask(const unsigned short, const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTaskInfo(const unsigned short, const QStringList&)),
			this, SLOT(fetchTaskInfo(const unsigned short, const QStringList&)));
}

TaskPreview::TaskPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget *parent) :
	QLineEdit(parent),
	_id(id),
	_listId(listId),
	_projectId(projectId),
	_controller(controller),
	_task(nullptr) {

	connects();

	emit getTaskName(_projectId, _listId, _id);
}

//TaskPreview::TaskPreview(QString taskName, const unsigned short id, const Controller* controller, QWidget *parent) :
//	QLineEdit(taskName, parent),
//	_id(id),
//	_controller(controller) {

//	connects();
//}

void TaskPreview::mouseDoubleClickEvent(QMouseEvent *event) {
	emit openTask(_id);
}

void TaskPreview::keyPressEvent(QKeyEvent *event) {
	QLineEdit::keyPressEvent(event);
	emit changedTaskName(_id, text().toStdString());
}

void TaskPreview::fetchTaskName(const unsigned short taskId, const QString& taskName) {
	if (_id == taskId) {
		setText(taskName);
	}
}

void TaskPreview::fetchTaskInfo(const unsigned short taskId, const QStringList& taskInfo) {
	if (taskId == _id) {
		_task = new TaskWidget(taskId, _listId, _projectId, _controller, taskInfo, this);
		switch (task_type_map.at(taskInfo[0].toStdString())) {
			case(TASK):
				break;
			case(TASK_CONTAINER):
				_task = new TaskWidget(taskId, _listId, _projectId, _controller, taskInfo, this);
				break;
			case(TASK_PRIORITY):
				_task = new TaskWidget(taskId, _listId, _projectId, _controller, taskInfo, this);
				break;
			case(TASK_PRIORITY_CONTAINER):
				_task = new TaskWidget(taskId, _listId, _projectId, _controller, taskInfo, this);
				break;
		}
	}
}

/*
void TPreview::mouseMoveEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		dragStartPos = event->pos();
	}
}

void TPreview::mousePressEvent(QMouseEvent *event) {
	if (!(event->buttons() & Qt::LeftButton)) {
		return;
	}
	if ((event->pos()-dragStartPos).manhattanLength() < QApplication::startDragDistance()) {
		return;
	}
		QDrag* drag = new QDrag(this);
		QMimeData* mimeData = new QMimeData();

}
*/
