#ifndef TASKCONTAINERWIDGET_H
#define TASKCONTAINERWIDGET_H

#include "taskwidget.h"

class TaskContainerWidget : public TaskWidget {
	Q_OBJECT
public:
	TaskContainerWidget();
	explicit TaskContainerWidget(QWidget* parent =nullptr);
	TaskContainerWidget(const TaskContainerWidget& widget,QWidget* parent =nullptr);
	TaskContainerWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr);
//	TaskContainerWidget(const QString& name, const QString& desc =QString(), QWidget* parent =nullptr); costruttore con parametro lista di task

signals:
	void addSubTask(unsigned short);

public slots:

};

#endif // TASKCONTAINERWIDGET_H
