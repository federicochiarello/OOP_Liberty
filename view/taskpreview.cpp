#include "taskpreview.h"

void TaskPreview::connects() {

	connect(this, SIGNAL(getTaskName(const unsigned short, const unsigned short, const unsigned short)),
			_controller, SLOT(onGetTaskName(const unsigned short, const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTaskName(const unsigned short, const unsigned short, const unsigned short, const QString&)),
			this, SLOT(fetchTaskName(const unsigned short, const unsigned short, const unsigned short, const QString&)));

	connect(this, SIGNAL(openTask(const unsigned short)),
			_controller, SLOT());
}

TaskPreview::TaskPreview(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, QWidget *parent) :
	QLineEdit(parent),
	_id(id),
	_listId(listId),
	_projectId(projectId),
	_controller(controller) {

	connects();
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

void TaskPreview::fetchTaskName(const unsigned short projectId, const unsigned short listId, const unsigned short taskId, const QString& taskName) {
	if (_id == taskId) {
		setText(taskName);
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
