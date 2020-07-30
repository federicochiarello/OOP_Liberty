#include "taskslistwidget.h"

TasksListWidget::TasksListWidget(std::string listName, QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()), _name(listName), _list(new QScrollArea(this)) {
	setup();
}

TasksListWidget::TasksListWidget(QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()), _name(std::string()), _list(new QScrollArea(this)) {

}

void TasksListWidget::setup() {

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

	/*
	_list->setDragEnabled(true);
	_list->setAcceptDrops(true);
	_list->setDropIndicatorShown(true);
	_list->setDefaultDropAction(Qt::MoveAction);
	_list->setModel(new QStringListModel());
	*/
	QWidget* widget = new QWidget(this);
	QVBoxLayout* tasksLayout = new QVBoxLayout();
	tasksLayout->addWidget(new QLineEdit(tr("1"), this));
	tasksLayout->addWidget(new QLineEdit(tr("2"), this));
	tasksLayout->addWidget(new QLineEdit(tr("3"), this));
	tasksLayout->addWidget(new QLineEdit(tr("4"), this));
	tasksLayout->addWidget(new QLineEdit(tr("5"), this));
	tasksLayout->addWidget(new QLineEdit(tr("6"), this));
	tasksLayout->addWidget(new QLineEdit(tr("7"), this));
	widget->setLayout(tasksLayout);

	_list->setWidget(widget);

	_layout->setAlignment(Qt::AlignLeft);
	_layout->addLayout(header);
	_layout->addWidget(_list);
	setLayout(_layout);
}

void TasksListWidget::addTask() {
	_list->widget()->layout()->addWidget(new QLineEdit(tr("prova"), this));
}

TasksListWidget::~TasksListWidget() {}
