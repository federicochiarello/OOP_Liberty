#ifndef TASKPRIORITYWIDGET_H
#define TASKPRIORITYWIDGET_H

#include "taskwidget.h"

class TaskPriorityWidget : public TaskWidget {
	Q_OBJECT
public:
	explicit TaskPriorityWidget(QWidget* parent =nullptr);
	TaskPriorityWidget(const TaskPriorityWidget& widget,QWidget* parent =nullptr);
	TaskPriorityWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr);

};

#endif // TASKPRIORITYWIDGET_H
