#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QLayout>
#include <QScrollArea>
#include <QDrag>
#include <QDropEvent>

#include <QLineEdit>

#include "taskwidget.h"

class TasksList : public QScrollArea {
	Q_OBJECT
public:
	explicit TasksList(QWidget *parent = nullptr);

	void addWidget(QWidget* widget);
protected:
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;
signals:

};

#endif // TASKSLIST_H
