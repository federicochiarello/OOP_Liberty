#include "taskprioritycontainerwidget.h"



TaskPriorityContainerWidget::TaskPriorityContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QStringList &taskInfo, QWidget *parent) :
	TaskWidget(id, listId, projectId, controller, taskInfo, parent) {}

TaskPriorityContainerWidget::TaskPriorityContainerWidget(const unsigned short id, const unsigned short listId, const unsigned short projectId, const Controller *controller, const QString &taskName, QWidget *parent) :
	TaskWidget(id, listId, projectId, controller, taskName, parent) {}
