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
	//QTextEdit* name = new TextHolder(tr("Inserire il nome del task"), this);
	//QTextEdit* desc = new TextHolder(tr("Descrizione"), this);
	QHBoxLayout* firstRow = new QHBoxLayout();
	QPushButton* options = new QPushButton(this);
	QMenu* menu = new QMenu(options);
	QAction* forward = new QAction(tr("Sposta avanti"), menu);
	QAction* backward = new QAction(tr("Sposta indietro"), menu);
	QAction* remove = new QAction(tr("Elimina"), menu);

	/* Connect delle varie QAction */
	//connect(forward, SIGNAL(triggered()));

	/* Scorciatoie per le QAction */
	/*
	forward->setShortcut(QKeySequence("Ctrl+L"));
	backward->setShortcut(QKeySequence(""));
	remove->setShortcut(QKeySequence("Shift+Ctrl+X"));
	*/

	/* Aggiunta QAction a menu */
	menu->addAction(forward);
	menu->addAction(backward);
	menu->addAction(remove);

	/* Aggiunta menu a pulsante e settaggio delle relative impostazioni */
	options->setMenu(menu);
	options->setFixedSize(25, 25);

	/* Settaggio impostazioni TextHolder _name */
	_name->setFixedHeight(25);
	_name->setMinimumWidth(150);
	_name->setMaximumWidth(300);
	_name->resize(150, 30);

	/* Aggiunta elementi a layout della prima riga e settaggi */
	firstRow->addWidget(_name);
	firstRow->addWidget(options);
	firstRow->setAlignment(Qt::AlignCenter);

	/* Aggiunta elementi a layout principale e settaggi */
	_layout->addLayout(firstRow);
	_layout->addWidget(_desc);
	setLayout(_layout);
	setSizePolicy(QSizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding));
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
	_name(new QLineEdit((taskInfo.size()>1?taskInfo[1]:""), this)),
	_desc(new TextHolder((taskInfo.size()>2?taskInfo[2]:""), this)) {

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
