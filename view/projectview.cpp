#include "projectview.h"

ProjectView::ProjectView(QWidget *parent) :
	QWidget(parent),
	_mainLayout(new QVBoxLayout()),
	_centralLayout(new QHBoxLayout()) {
	setup();
	//addList("Prova");
}

ProjectView::ProjectView(const std::pair<unsigned short, QString>& projectInfo, QWidget *parent) :
	QWidget(parent),
	_id(projectInfo.first) {

}

void ProjectView::setup(std::string name) {
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setLayout(_mainLayout);
	{
		QLineEdit* title = new QLineEdit(QString::fromStdString(name), this);
		_mainLayout->addWidget(title);
	}

	{
		QPushButton* new_ = new QPushButton(tr("+"), this);
		connect(new_, SIGNAL(clicked()), this, SLOT(newList()));
		_centralLayout->addWidget(new_);
	}
	_mainLayout->addLayout(_centralLayout);
}

void ProjectView::newList() {
	//TasksList* newTaskList = new TasksList(this);
	_lists.push_back(new TasksListWidget(this));
	//QLineEdit* listName = new QLineEdit(tr(""), this);
	//connect(_lists.back(), SIGNAL(newList()), this, SLOT(addList()));
	_centralLayout->insertWidget(_centralLayout->count()-1, _lists.back());
}


void ProjectView::addList(std::string listName) {
	_mainLayout->addWidget(dynamic_cast<TasksListWidget*>(_lists.back()));
}
