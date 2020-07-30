#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QObject>
#include <QWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QShortcut>

#include <vector>
#include <string>

#include "taskslistwidget.h"

class ProjectView : public QWidget {
	Q_OBJECT
	std::vector<QWidget*> _lists;
	QVBoxLayout* _mainLayout;
	QHBoxLayout* _centralLayout;

	void setup(std::string name = std::string());
public:
	explicit ProjectView(QWidget *parent = nullptr);

private slots:
	void newList();

public slots:
	void addList(std::string listName =std::string());

	signals:

};

#endif // PROJECTVIEW_H
