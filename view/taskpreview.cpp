#include "taskpreview.h"

TaskPreview::TaskPreview(QWidget *parent) : QLineEdit(parent), _id(int()) {

}

TaskPreview::TaskPreview(int id, QWidget *parent) : QLineEdit(parent), _id(id) {

}

void TaskPreview::mouseDoubleClickEvent(QMouseEvent *event) {
	TaskWidget* clickedTask = new TaskWidget();
	clickedTask->show();
	emit openTaskInfo(_id);
}

void TaskPreview::keyPressEvent(QKeyEvent *event) {
	QLineEdit::keyPressEvent(event);
	emit changedTaskName(_id, text().toStdString());
}

void TaskPreview::setTaskName(std::string taskName) {
	setText(QString::fromStdString(taskName));
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
