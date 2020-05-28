#include "taskwidget.h"

QSize TaskWidget::minSize = QSize(150, 30);
QSize TaskWidget::maxSize = QSize(300, 270);

TaskWidget::TaskWidget(QWidget* parent) :
	QWidget(parent),
	_layout(new QVBoxLayout()),
	_title(new QTextEdit(this)),
	_desc(new QTextEdit(this)) {
	setup();
}

TaskWidget::TaskWidget(const QString& title, const QString& desc, QWidget* parent) :
	QWidget(parent),
	_layout(new QVBoxLayout()),
	_title(new QTextEdit(title, this)),
	_desc(new QTextEdit(desc, this)) {


}

void TaskWidget::setup() {
	QHBoxLayout* firstRow = new QHBoxLayout();
	QTextEdit* name = new TextHolder(tr("Inserire il nome del task"), this);
	QToolButton* options = new QToolButton(this);
	QTextEdit* desc = new TextHolder(tr("Descrizione"), this);
	firstRow->addWidget(name);
	firstRow->addWidget(options);
	_layout->addLayout(firstRow);
	_layout->addWidget(desc);
	setLayout(_layout);
	setGeometry(0,0,minSize.width(), minSize.height());
	setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));
	setMaximumSize(maxSize);
}

/*
void TaskWidget::mousePressEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		(childAt(event->pos()))->setFocus();
	} else if (event->button() == Qt::RightButton) {

	} else {

	}
}
*/
