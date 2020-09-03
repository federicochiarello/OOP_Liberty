#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLayout>
#include <QLineEdit>
#include <QTextEdit>
#include <QMenu>
#include <QPushButton>

#include "controller/controller.h"

class TaskWidget : public QWidget {
	Q_OBJECT

	const unsigned short _id;
	const unsigned short _listId;
	const unsigned short _projectId;
	const Controller* _controller;

	QVBoxLayout*	_layout;
	QHBoxLayout* _header;
	QLineEdit*		_name;
	QTextEdit*		_description;

	QPushButton* _options;
	QMenu* _menu;
	QAction* _actionMoveLeft;
	QAction* _actionMoveRight;
	QAction* _actionDelete;

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
