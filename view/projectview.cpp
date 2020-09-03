#include "projectview.h"

//ProjectView::ProjectView(QWidget *parent) :
//	QWidget(parent),
//	_mainLayout(new QVBoxLayout()),
//	_centralLayout(new QHBoxLayout()) {
//	setup();
//	//addList("Prova");
//}

ProjectView::ProjectView(const std::pair<unsigned short, QString>& projectInfo, const Controller* controller, QWidget *parent) :
	QWidget(parent),
	_id(projectInfo.first),
	_lists(),
	_controller(controller),
	_mainLayout(new QVBoxLayout()),
	_headerLayout(new QHBoxLayout()),
	_centralLayout(new QHBoxLayout()),
	_projectName(new QLineEdit(projectInfo.second, this)),
	_options(new QPushButton(this)),
	_optionMenu(new QMenu(_options)),
	_actionExportProject(new QAction(tr("Esporta progetto"), _optionMenu)),
	_buttonAddList(new QPushButton(tr("+"), this)),
	_centralWidget(new QScrollArea(this)),
	_listsWidget(new QWidget(_centralWidget)) {

	setup();
	connects();
	qDebug() << "Project created";

	emit getLists(_id);
}

unsigned short ProjectView::getId() const { return _id; }

void ProjectView::connects() {

//	Usare editingFinished() per determinare quando cambiare nome
	connect(_projectName, SIGNAL(editingFinished()),
			this, SLOT(onProjectNameChanged()));

	connect(this, SIGNAL(projectNameChanged(const unsigned short, const QString&)),
			_controller, SLOT(onProjectNameChanged(const unsigned short, const QString&)));

	connect(_controller, SIGNAL(setProjectName(const unsigned short, const QString&)),
			this, SLOT(onSetProjectName(const unsigned short, const QString&)));

	connect(this, SIGNAL(addNewList(const unsigned short)),
			_controller, SLOT(onAddNewList(const unsigned short)));

	connect(_controller, SIGNAL(sendListId(const unsigned short, const unsigned short)),
			this, SLOT(fetchListId(const unsigned short, const unsigned short)));

	connect(this, SIGNAL(getLists(const unsigned short)),
			_controller, SLOT(onGetLists(const unsigned short)));

    connect(_controller, SIGNAL(sendListsIds(const unsigned short, veqtor<unsigned short>)),
            this, SLOT(fetchListsIds(const unsigned short, veqtor<unsigned short>)));

	connect(_actionExportProject, SIGNAL(triggered()),
			this, SLOT(onExportProject()));

	connect(this, SIGNAL(exportProject(const unsigned short, const QString&)),
			_controller, SLOT(onExportProject(const unsigned short, const QString&)));

	connect(_buttonAddList, SIGNAL(clicked()),
			this, SLOT(onAddNewList()));

	connect(_controller, SIGNAL(moveList(const unsigned short, const unsigned short, const Direction&)),
			this, SLOT(onMoveList(const unsigned short, const unsigned short, const Direction&)));

}

void ProjectView::setup() {
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setLayout(_mainLayout);

	_options->setMenu(_optionMenu);
	_optionMenu->addAction(_actionExportProject);

	_headerLayout->addWidget(_projectName);
	_headerLayout->addWidget(_options);

	_centralLayout->addWidget(_buttonAddList);
	_listsWidget->setLayout(_centralLayout);
	_listsWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	_centralWidget->setWidgetResizable(true);
	_centralWidget->setWidget(_listsWidget);

	_mainLayout->addLayout(_headerLayout);
	_mainLayout->addWidget(_centralWidget);
}

//ProjectView::ProjectView(const unsigned short id, const Controller *controller, QWidget *parent) :
//	_id(id),
//	_lists(),
//	_controller(controller) {

//}

void ProjectView::newList() {
	//TasksList* newTaskList = new TasksList(this);
//	_lists.push_back(new TasksListWidget(this));
	//QLineEdit* listName = new QLineEdit(tr(""), this);
	//connect(_lists.back(), SIGNAL(newList()), this, SLOT(addList()));
	//	_centralLayout->insertWidget(_centralLayout->count()-1, _lists.back());
}

void ProjectView::onExportProject() {
	emit exportProject(_id, QFileDialog::getExistingDirectory(this, tr("Esporta"), QDir::homePath())+_projectName->text());
}


void ProjectView::onAddNewList() {
	emit addNewList(_id);
	//	_mainLayout->addWidget(dynamic_cast<TasksListWidget*>(_lists.back()));
}

void ProjectView::fetchListId(const unsigned short projectId, const unsigned short listId) {
	if (projectId == _id) {
		TasksListWidget* newList = new TasksListWidget(listId, projectId, true, _controller, this);
		_lists.push_back(newList);
		_centralLayout->insertWidget(_centralLayout->count()-1, newList);
		_centralWidget->setWidget(_listsWidget);
	}
}

void ProjectView::onProjectNameChanged() {
	emit projectNameChanged(_id, _projectName->text());
}

void ProjectView::onSetProjectName(const unsigned short projectId, const QString& projectName) {
	if (projectId == _id) {
		_projectName->setText(projectName);
	}
}

void ProjectView::onMoveList(const unsigned short projectId, const unsigned short listId, const Direction& moveDirection) {
	if (projectId == _id) {
		TasksListWidget* tmp;
		for (auto i = 0; i < _centralLayout->count()-1; i++) {
			if ((tmp = dynamic_cast<TasksListWidget*>(_centralLayout->itemAt(i)->widget())) && (tmp->getId() == listId)) {
				switch (moveDirection) {
					case LEFT:
						_centralLayout->removeWidget(tmp);
						_centralLayout->insertWidget(i-1, tmp);
						break;
					case RIGHT:
						_centralLayout->removeWidget(tmp);
						_centralLayout->insertWidget(++i, tmp);
						break;
				}
			}
		}
	}
}

void ProjectView::fetchListsIds(const unsigned short projectId, veqtor<unsigned short> listsIds) {
	if (_id == projectId) {
		qDebug() << "fetchLists";
		for (auto listId : listsIds) {
			TasksListWidget* list = new TasksListWidget(listId, _id, false, _controller, this);
			_lists.push_back(list);
			_centralLayout->insertWidget(_centralLayout->count()-1, list);
			_centralWidget->setWidget(_listsWidget);
//			connect(list, SIGNAL(getListName(const unsigned short)),
//					this, SIGNAL(getListName(const unsigned short)));

//			connect(this, SIGNAL(sendListName(const unsigned short, const QString&)),
//					list, SLOT(fetchListName(const unsigned short, const QString&)));

//			connect(this, SIGNAL(sendTasksIds(const unsigned short, const veqtor<std::pair<unsigned short, TaskType>>)),
//					list, SLOT(fetchTasksIds(const unsigned short, const veqtor<std::pair<unsigned short, TaskType>>))); eliminato


//			emit list->getListName(list->getId());
		}
	}
}

//void ProjectView::onGetListName(const unsigned short listId) {
//	emit getListName(_id, listId);
//}

//void ProjectView::fetchListName(const unsigned short projectId, const unsigned short listId, const QString& listName) {
//	if (projectId == _id) {
//		emit sendListName(listId, listName);
//	}
//}

//void ProjectView::onGetTasksIds(const unsigned short listId) {
//	emit getTasksIds(_id, listId);
//}
