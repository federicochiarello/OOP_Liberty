#include "tpreview.h"

TPreview::TPreview(QWidget *parent) : QWidget(parent), _layout(new QHBoxLayout()) {
	setup();
}

void TPreview::setup() {
	setLayout(_layout);

	TextHolder* title = new TextHolder(this);
	QToolButton* options = new QToolButton(this);

	layout()->addWidget(title);
	layout()->addWidget(options);
}

void TPreview::mouseDoubleClickEvent(QMouseEvent *event) {
	TaskWidget* clickedTask = new TaskWidget();
	clickedTask->show();
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
