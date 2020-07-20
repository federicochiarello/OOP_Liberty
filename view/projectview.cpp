#include "projectview.h"

ProjectView::ProjectView(QWidget *parent) : QWidget(parent), _mainLayout(new QHBoxLayout()) {
	setLayout(_mainLayout);
	addList("Prova");
}

void ProjectView::addList(std::string listName) {
	//_lists.push_back(*(new TasksList(this)));
	_mainLayout->addWidget(_lists.back());
}
