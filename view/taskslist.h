#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>

#include "taskwidget.h"
#include "tpreview.h"

#include <QDebug>

class TasksList : public QWidget {
	Q_OBJECT
public:
	TasksList(QWidget* parent =nullptr);
private:
	QVBoxLayout* _layout;

	void setup();
public slots:
	void addTask();
};

#endif // TASKSLIST_H
