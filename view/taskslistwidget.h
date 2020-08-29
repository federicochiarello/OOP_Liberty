#ifndef TASKSLISTWIDGET_H
#define TASKSLISTWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenu>
#include <QLabel>
#include <QLineEdit>
#include <QScrollArea>

#include "taskslist.h"
#include <QDebug>

class TasksListWidget : public QWidget {
	Q_OBJECT

	unsigned short _id;
	QLineEdit* _title;
	QVBoxLayout* _layout;
	std::string _name;
	TasksList* _list;

	void setup();

public:

	explicit TasksListWidget(QWidget* parent =nullptr);
	explicit TasksListWidget(QString listName, QWidget* parent =nullptr);
	TasksListWidget(const unsigned short listId, QWidget* parent =nullptr);
	~TasksListWidget();

	unsigned short getId() const;

signals:

	void getListName(const unsigned short);
	void moveTaskForward(const unsigned short);
	void moveTaskBackward(const unsigned short);

public slots:

	void fetchListName(const unsigned short listId, const QString& listName);
	//	void addTask();
};

#endif // TASKSLISTWIDGET_H
