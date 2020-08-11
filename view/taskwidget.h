#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QTextEdit>
#include <QMenu>
#include <QPushButton>

//#include <QLabel>
//#include <QToolButton>

#include "textholder.h"

class TaskWidget : public QWidget {
	Q_OBJECT
	QVBoxLayout*	_layout;
	TextHolder*		_name;
	TextHolder*		_desc;

	void setup();
public:
	explicit TaskWidget(QWidget* parent =nullptr);
	TaskWidget(const TaskWidget& widget,QWidget* parent =nullptr);
	TaskWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr);

	void setName();
	void setDesc();

protected:
	//void mousePressEvent(QMouseEvent *event) override;

signals:
	QString getData() const;
};

#endif // TASKWIDGET_H
