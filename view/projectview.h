#ifndef PROJECTVIEW_H
#define PROJECTVIEW_H

#include <QObject>
#include <QWidget>
#include <QHBoxLayout>
#include <QShortcut>
#include <QFileDialog>

#include <vector>
#include <string>

#include "src/globalenums.h"

#include "controller/controller.h"

#include "taskslistwidget.h"

class ProjectView : public QWidget {
	Q_OBJECT

	const unsigned short _id;
    veqtor<TasksListWidget*> _lists;
	const Controller* _controller;

	QVBoxLayout* _mainLayout;
	QHBoxLayout* _headerLayout;
	QHBoxLayout* _centralLayout;

	QLineEdit* _projectName;
	QPushButton* _options;
	QMenu* _optionMenu;
	QAction* _actionExportProject;
	QPushButton* _buttonAddList;
	QScrollArea* _centralWidget;
	QWidget* _listsWidget;

	void connects();
	void setup();

public:

	ProjectView(const std::pair<unsigned short, QString>& projectInfo, const Controller* controller, QWidget* parent =nullptr);

	unsigned short getId() const;

signals:

	void exportProject(const unsigned short, const QString&);
	void getLists(const unsigned short);
	void addNewList(const unsigned short);
	void projectNameChanged(const unsigned short, const QString&);
	void changeProjectName(unsigned short, std::string);

public slots:

	void onExportProject();
    void fetchListsIds(const unsigned short projectId, veqtor<unsigned short> listsIds);
	void onAddNewList();
	void fetchListId(const unsigned short projectId, const unsigned short listId);
	void onProjectNameChanged();
	void onSetProjectName(const unsigned short projectId, const QString& projectName);
	void onMoveList(const unsigned short projectId, const unsigned short listId, const Direction& moveDirection);
};

#endif // PROJECTVIEW_H
