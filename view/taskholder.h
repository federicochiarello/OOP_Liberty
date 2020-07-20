#ifndef TASKHOLDER_H
#define TASKHOLDER_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QScrollArea>
#include <QPushButton>

#include "textholder.h"
#include "taskwidget.h"
#include "taskslist.h"

class TaskHolder : public QWidget {
	Q_OBJECT
public:
	explicit TaskHolder(QWidget *parent = nullptr);

private slots:
	void addTask();

private:
	QVBoxLayout* _layout;
	QScrollArea* _scrollArea;
	TasksList* _tasks;

	void setup();
	void genLayout();
signals:

};

#endif // TASKHOLDER_H
