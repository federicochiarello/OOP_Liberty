#ifndef TASKSLIST_H
#define TASKSLIST_H

#include <QObject>
#include <QLayout>
#include <QScrollArea>
#include <QDrag>
#include <QDropEvent>
#include <QMimeData>

#include <QLineEdit>

//#include "taskwidget.h"
#include "taskpreview.h"

class TasksList : public QScrollArea {
	Q_OBJECT

	QVBoxLayout* _layout;
	QWidget* _widget;
public:
	explicit TasksList(QWidget *parent = nullptr);

	void addWidget(QLineEdit* widget);
protected:
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

public slots:
	void addTask();
signals:
	void newTask(unsigned short);
	void deleteTask(unsigned short);

};

class DragDrop : public QWidget {
	Q_OBJECT
public:
	explicit DragDrop(QWidget* parent =nullptr);

protected:
	virtual void dragMoveEvent(QDragMoveEvent* event) override;
	virtual void dragEnterEvent(QDragEnterEvent* event) override;
	virtual void dragLeaveEvent(QDragLeaveEvent* event) override;
	virtual void dropEvent(QDropEvent* event) override;
	virtual void mousePressEvent(QMouseEvent* event) override;

};

#endif // TASKSLIST_H
