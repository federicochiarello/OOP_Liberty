#include "taskprioritywidget.h"



TaskPriorityWidget::TaskPriorityWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QStringList &taskInfo, QWidget *parent) :
	TaskWidget(id, listId, projectId, controller, taskInfo, parent) {}

TaskPriorityWidget::TaskPriorityWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QString &taskName, QWidget *parent):
	TaskWidget(id, listId, projectId, controller, taskName, parent) {}
