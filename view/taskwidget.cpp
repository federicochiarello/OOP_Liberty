#include "taskwidget.h"

//TaskWidget::TaskWidget(QWidget* parent) :
//	QWidget(parent),
//	_layout(new QVBoxLayout()),
//	_name(new QLineEdit(this)),
//	_desc(new TextHolder(this)) {
//	setup();
//}

//TaskWidget::TaskWidget(const QString& name, const QString& desc, QWidget* parent) :
//	QWidget(parent),
//	_layout(new QVBoxLayout()),
//	_name(new QLineEdit(name, this)),
//	_desc(new TextHolder(desc, this)) {
//	setup();
//}

void TaskWidget::setup() {


	/* Connect delle varie QAction */
	//connect(forward, SIGNAL(triggered()));

	/* Scorciatoie per le QAction */
	/*
	forward->setShortcut(QKeySequence("Ctrl+L"));
	backward->setShortcut(QKeySequence(""));
	remove->setShortcut(QKeySequence("Shift+Ctrl+X"));
	*/

	/* Aggiunta QAction a menu */
	_menu->addAction(_actionMoveLeft);
	_menu->addAction(_actionMoveRight);
	_menu->addAction(_actionDelete);

	/* Aggiunta menu a pulsante e settaggio delle relative impostazioni */
	_options->setMenu(_menu);

	/* Settaggio impostazioni TextHolder _name */

	/* Aggiunta elementi a layout della prima riga e settaggi */
	_header->addWidget(_name);
	_header->addWidget(_options);
	_header->setAlignment(Qt::AlignCenter);

	/* Aggiunta elementi a layout principale e settaggi */
	_layout->addLayout(_header);
	_layout->addWidget(_desc);
	setLayout(_layout);
	setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::MinimumExpanding));
}

void TaskWidget::connects() {
	connect(_name, SIGNAL(editingFinished()),
			this, SLOT(onTaskNameChanged()));

	connect(this, SIGNAL(taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)),
			_controller, SLOT(onTaskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&)));

	connect(this, SIGNAL(updateTaskPreviewName(const unsigned short, const QString&)),
			_controller, SLOT(onUpdateTaskPreviewName(const unsigned short, const QString&)));
}

TaskWidget::TaskWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QStringList& taskInfo, QWidget *parent) :
	QWidget(parent),
	_id(id),
	_listId(listId),
	_projectId(projectId),
	_controller(controller),
	_layout(new QVBoxLayout()),
	_header(new QHBoxLayout()),
	_name(new QLineEdit((taskInfo.size()>1?taskInfo[1]:""), this)),
	_desc(new TextHolder((taskInfo.size()>2?taskInfo[2]:""), this)),
	_options(new QPushButton(this)),
	_menu(new QMenu(_options)),
	_actionMoveLeft(new QAction(tr("Sposta a sinistra"), _menu)),
	_actionMoveRight(new QAction(tr("Sposta a destra"), _menu)),
	_actionDelete(new QAction(tr("Elimina"), _menu)) {

	setup();
}

TaskWidget::TaskWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QString &taskName, QWidget *parent) :
	QWidget(parent),
	_id(id),
	_listId(listId),
	_projectId(projectId),
	_controller(controller),
	_layout(new QVBoxLayout()),
	_name(new QLineEdit(taskName, this)),
	_desc(new TextHolder(this)) {

	setup();
}

void TaskWidget::onTaskNameChanged() {
	emit taskNameChanged(_projectId, _listId, _id, _name->text());
	emit updateTaskPreviewName(_id, _name->text());
}
