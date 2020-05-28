#include "taskslist.h"

TasksList::TasksList(QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()) {
	setup();
}

void TasksList::setup() {
	setMinimumWidth(TaskWidget::minSize.width());
	setGeometry(0, 0, 300, 200);
	setLayout(_layout);
	layout()->setAlignment(Qt::AlignTop);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
}

void TasksList::addTask() {

	TPreview* task = new TPreview(this);
	_layout->addWidget(task);
}
