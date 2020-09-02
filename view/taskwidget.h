#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenu>
#include <QPushButton>

//#include <QLabel>
//#include <QToolButton>

#include "controller/controller.h"

#include "textholder.h"

class TaskWidget : public QWidget {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _listId;
	const unsigned short _projectId;
	const Controller* _controller;

	QVBoxLayout*	_layout;
	QLineEdit*		_name;
	TextHolder*		_desc;

	void setup();
	void connects();
public:
	TaskWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QStringList& taskInfo, QWidget* parent =nullptr);
	TaskWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller* controller, const QString& taskName, QWidget* parent =nullptr);
//	TaskWidget(const TaskWidget& widget,QWidget* parent =nullptr);
//	TaskWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr);

	void setName();
	void setDesc();

protected:
	//void mousePressEvent(QMouseEvent *event) override;

signals:

	void updateTaskPreviewName(const unsigned short, const QString&);
	void taskNameChanged(const unsigned short, const unsigned short, const unsigned short, const QString&);

public slots:
	void onTaskNameChanged();
};

#endif // TASKWIDGET_H
