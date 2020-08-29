#include "taskslistwidget.h"

void TasksListWidget::setup() {
	// setMinimumSize()
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

	_title->setFocus();

	QPushButton* button = new QPushButton(tr("Actions"), this);
	QMenu* menu = new QMenu(button);
	QAction* add = new QAction(tr("Add Task"), menu);

	menu->addAction(add);
	button->setMenu(menu);

	connect(add, SIGNAL(triggered()), _list, SLOT(addTask()));

	QHBoxLayout* header = new QHBoxLayout();
	header->setAlignment(Qt::AlignVCenter);
	header->addWidget(_title);
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

TasksListWidget::TasksListWidget(QString listName, QWidget* parent) :
	QWidget(parent),
	_title(new QLineEdit(listName, this)),
	_layout(new QVBoxLayout()),
	_list(new TasksList(this)) {

	setup();
}

TasksListWidget::TasksListWidget(const unsigned short listId, QWidget *parent) :
	QWidget(parent),
	_id(listId),
	_title(new QLineEdit(this)),
	_list(new TasksList(this)) {

	setup();
}


TasksListWidget::TasksListWidget(QWidget* parent) :
	QWidget(parent),
	_layout(new QVBoxLayout()),
	_name(std::string()),
	_list(new TasksList(this)) {
	setup();
}

//void TasksListWidget::addTask() {
//	_list->widget()->layout()->addWidget(new QLineEdit(tr("prova"), this));
//}

TasksListWidget::~TasksListWidget() {}

unsigned short TasksListWidget::getId() const { return _id; }

void TasksListWidget::fetchListName(const unsigned short listId, const QString &listName) {
	if (listId == _id) {
		_title->setText(listName);
	}
}

