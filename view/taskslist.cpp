#include "taskslist.h"

TasksList::TasksList(QWidget *parent) : QScrollArea(parent) {
	setAcceptDrops(true);
	QVBoxLayout* wdgtLayout = new QVBoxLayout();
	QWidget* wdgt = new QWidget(this);
	wdgt->setLayout(wdgtLayout);
	setWidget(wdgt);
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));
	addWidget(new QLineEdit(this));

}

void TasksList::addWidget(QWidget* wdgt) {
	widget()->layout()->addWidget(wdgt);
}

void TasksList::dragMoveEvent(QDragMoveEvent* event) { // spostamento task all'interno della lista

}

void TasksList::dragEnterEvent(QDragEnterEvent* event) { // spostamento di un task da un'altra lista all'interno di quella corrente

}

void TasksList::dragLeaveEvent(QDragLeaveEvent* event) { // spostamento di un task al di fuori della lista corrente

}

void TasksList::dropEvent(QDropEvent* event) { // aggiunta di un task alla lista da un'altra lista

}
