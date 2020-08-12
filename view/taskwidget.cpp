#include "taskwidget.h"

TaskWidget::TaskWidget(QWidget* parent) :
	QWidget(parent),
	_layout(new QVBoxLayout()),
	_name(new QLineEdit(this)),
	_desc(new TextHolder(this)) {
	setup();
}

TaskWidget::TaskWidget(const QString& name, const QString& desc, QWidget* parent) :
	QWidget(parent),
	_layout(new QVBoxLayout()),
	_name(new QLineEdit(name, this)),
	_desc(new TextHolder(desc, this)) {
	setup();
}

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
