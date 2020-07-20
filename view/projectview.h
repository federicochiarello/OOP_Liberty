#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>

#include <vector>
#include <string>

#include "taskslist.h"

class ProjectView : public QWidget {
	Q_OBJECT
	std::vector<QListWidget*> _lists;
	QHBoxLayout* _mainLayout;
public:
	explicit ProjectView(QWidget *parent = nullptr);

	void addList(std::string listName);

	signals:

};

#endif // PROJECTVIEW_H
