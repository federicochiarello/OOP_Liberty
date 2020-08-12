#include "taskslistwidget.h"

void TasksListWidget::setup() {
	// setMinimumSize()
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	QLineEdit* title = new QLineEdit(QString::fromStdString(_name), this);
	title->setFocus();

	QPushButton* button = new QPushButton(tr("Actions"), this);
	QMenu* menu = new QMenu(button);
	QAction* add = new QAction(tr("Add Task"), menu);

	menu->addAction(add);
	button->setMenu(menu);

	connect(add, SIGNAL(triggered()), _list, SLOT(addTask()));

	QHBoxLayout* header = new QHBoxLayout();
	header->setAlignment(Qt::AlignVCenter);
	header->addWidget(title);
	header->addWidget(button);

	/*
	_list->setDragEnabled(true);
	_list->setAcceptDrops(true);
	_list->setDropIndicatorShown(true);
	_list->setDefaultDropAction(Qt::MoveAction);
	_list->setModel(new QStringListModel());
	_list->setWidget(widget);
	*/


	_layout->setAlignment(Qt::AlignLeft);
	_layout->addLayout(header);
	_layout->addWidget(_list);
	setLayout(_layout);
}

TasksListWidget::TasksListWidget(std::string listName, QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()), _name(listName), _list(new TasksList(this)) {
	setup();
}


TasksListWidget::TasksListWidget(QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()), _name(std::string()), _list(new TasksList(this)) {
	setup();
}

//void TasksListWidget::addTask() {
//	_list->widget()->layout()->addWidget(new QLineEdit(tr("prova"), this));
//}

TasksListWidget::~TasksListWidget() {}

