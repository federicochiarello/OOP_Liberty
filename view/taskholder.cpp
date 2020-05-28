#include "taskholder.h"

QSize TaskHolder::minSize = QSize(TaskWidget::minSize.width()+100, TaskWidget::minSize.height());
QSize TaskHolder::maxSize = QSize(TaskWidget::maxSize.width(), TaskWidget::maxSize.height());

TaskHolder::TaskHolder(QWidget* parent) : QWidget(parent), _layout(new QVBoxLayout()), _scrollArea(new QScrollArea(this)), _tasks(new TasksList(this)) {
	setup();
}

void TaskHolder::addTask() {
	_tasks->addTask();
	_scrollArea->setWidget(_tasks);
}

void TaskHolder::setup() {
	genLayout();
	setMinimumSize(minSize);
	setMaximumSize(maxSize);
	setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding));
}

void TaskHolder::genLayout() {
	QHBoxLayout* firstRow = new QHBoxLayout();

	QTextEdit* name = new TextHolder(tr("Inserire nome lista"), this);
	QPushButton* options = new QPushButton(this);

	options->setFixedSize(30, 30);

	QMenu* menu = new QMenu(options);
	QAction* newTask = new QAction(tr("New task"), menu);

	menu->addAction(newTask);
	options->setMenu(menu);

	_scrollArea->setWidget(_tasks);
	_scrollArea->setWidgetResizable(true);
	//connect(options, SIGNAL(clicked()), newTask, SLOT());
	connect(newTask,  SIGNAL(triggered()), _scrollArea->widget(), SLOT(addTask()));

	firstRow->addWidget(name);
	//firstRow->addWidget(newTask);
	firstRow->addWidget(options);

	_layout->addLayout(firstRow);
	_layout->addWidget(_scrollArea);
	setLayout(_layout);
}