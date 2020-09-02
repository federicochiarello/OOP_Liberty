#include "taskslistwidget.h"

void TasksListWidget::setup() {
	// setMinimumSize()
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

//	_title->setFocus();

	_menu->addAction(_actionNewTask);
	_buttonActions->setMenu(_menu);

	_header->setAlignment(Qt::AlignVCenter);
	_header->addWidget(_title);
	_header->addWidget(_buttonActions);

	/*
	_list->setDragEnabled(true);
	_list->setAcceptDrops(true);
	_list->setDropIndicatorShown(true);
	_list->setDefaultDropAction(Qt::MoveAction);
	_list->setModel(new QStringListModel());
	_list->setWidget(widget);
	*/


	_layout->setAlignment(Qt::AlignLeft);
	_layout->addLayout(_header);
	_layout->addWidget(_list);
	setLayout(_layout);
}

void TasksListWidget::connects() {
	connect(_actionNewTask, SIGNAL(triggered()),
			_list, SLOT(onNewTask()));

	connect(_controller, SIGNAL(sendTaskId(const unsigned short, const std::pair<unsigned short, TaskType>&)),
			this, SLOT(fetchTaskId(const unsigned short, const std::pair<unsigned short, TaskType>&)));

	connect(_title, SIGNAL(editingFinished()),
			this, SLOT(onListNameChanged()));

	connect(this, SIGNAL(listNameChanged(const unsigned short, const unsigned short, const QString&)),
			_controller, SLOT(onListNameChanged(const unsigned short, const unsigned short, const QString&)));

	connect(this, SIGNAL(getListName(const unsigned short, const unsigned short)),
			_controller, SLOT(onGetListName(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendListName(const unsigned short, const QString&)),
			this, SLOT(fetchListName(const unsigned short, const QString&)));

	connect(this, SIGNAL(getTasksIds(const unsigned short, const unsigned short)),
			_controller, SLOT(onGetTasksIds(const unsigned short, const unsigned short)));

	connect(_controller, SIGNAL(sendTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>&)),
			this, SLOT(fetchTasksIds(const unsigned short, const std::vector<std::pair<unsigned short, TaskType>>&)));
}

//TasksListWidget::TasksListWidget(QString listName, QWidget* parent) :
//	QWidget(parent),
//	_title(new QLineEdit(listName, this)),
//	_layout(new QVBoxLayout()),
//	_list(new TasksList(this)) {

//	setup();
//}

TasksListWidget::TasksListWidget(const unsigned short listId, const unsigned short projectId, const bool& isNew, const Controller* controller, QWidget *parent) :
	QWidget(parent),
	_id(listId),
	_projectId(projectId),
	_controller(controller),
	_layout(new QVBoxLayout()),
	_header(new QHBoxLayout()),
	_title(new QLineEdit(this)),
	_buttonActions(new QPushButton("Actions", this)),
	_menu(new QMenu(_buttonActions)),
	_actionNewTask(new QAction(tr("Nuovo task"), _menu)),
	_list(new TasksList(_id, _projectId, controller, this)) {

	setup();
	connects();

	if (!isNew) {
		emit getListName(_projectId, _id);
		emit getTasksIds(_projectId, _id);
	}
}


//TasksListWidget::TasksListWidget(QWidget* parent) :
//	QWidget(parent),
//	_layout(new QVBoxLayout()),
//	_name(std::string()),
//	_list(new TasksList(this)) {
//	setup();
//}

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

void TasksListWidget::fetchTaskId(const unsigned short listId, const std::pair<unsigned short, TaskType> &taskId) {
	if (listId == _id) {
		_list->addTask(taskId);
		qDebug() << "Nuovo Task Id" << taskId.first;
	}
}

void TasksListWidget::fetchTasksIds(const unsigned short listId, const std::vector<std::pair<unsigned short, TaskType>>& tasksIds) {
	if (listId == _id) {
		for (auto taskId: tasksIds) {
			_list->addTask(taskId);
		}
	}
}

void TasksListWidget::onListNameChanged() {
	emit listNameChanged(_projectId, _id, _title->text());
}

