#include "taskslist.h"

TasksList::TasksList(QWidget* parent, std::string listName) : QWidget(parent), _layout(new QVBoxLayout()), _name(listName), _list(new QListView(this)) {
	setup();
}

void TasksList::setup() {

	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));

	QLineEdit* title = new QLineEdit(QString::fromStdString(_name), this);

	QPushButton* button = new QPushButton(tr("Actions"), this);
	QMenu* menu = new QMenu(button);
	QAction* add = new QAction(tr("Add Task"), menu);

	menu->addAction(add);
	button->setMenu(menu);

	connect(add, SIGNAL(triggered()), this, SLOT(addTask()));

	QHBoxLayout* header = new QHBoxLayout();
	header->setAlignment(Qt::AlignVCenter);
	header->addWidget(title);
	header->addWidget(button);


	_list->setDragEnabled(true);
	_list->setAcceptDrops(true);
	_list->setDropIndicatorShown(true);
	_list->setDefaultDropAction(Qt::MoveAction);
	_list->setModel(new QStringListModel());

	_layout->setAlignment(Qt::AlignLeft);
	_layout->addLayout(header);
	_layout->addWidget(_list);
	setLayout(_layout);
}

void TasksList::addTask() {
	_list->model()->insertRow(_list->model()->rowCount());
	QModelIndex oIndex = _list->model()->index(_list->model()->rowCount() - 1, 0);

	_list->edit(oIndex);
}
