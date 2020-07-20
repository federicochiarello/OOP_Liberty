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
public:
	explicit TaskWidget(QWidget* parent =nullptr);
	TaskWidget(const TaskWidget& widget,QWidget* parent =nullptr);
	TaskWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr);

	void setName();
	void setDesc();
protected:
	//void mousePressEvent(QMouseEvent *event) override;
private:
	QVBoxLayout*	_layout;
	TextHolder*		_name;
	TextHolder*		_desc;

	void setup();
};

#endif // TASKWIDGET_H
