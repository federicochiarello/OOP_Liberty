#include "projectpreview.h"

void ProjectPreview::connects() {
	connect(this, SIGNAL(openProject(const QString&)),
			_controller, SLOT(onOpenProject(const QString&)));
}

ProjectPreview::ProjectPreview(const Controller* controller, const QString& name, const QString& pathToDir, QWidget *parent) :
	QWidget(parent),
	_controller(controller),
	_layout(new QVBoxLayout(this)),
	_name(new QLabel(name.left(name.lastIndexOf(".")), this)),
	_path(new QLabel(pathToDir+"/"+name, this)) {

	connects();

	_layout->addWidget(_name);
	_layout->addWidget(_path);
}

void ProjectPreview::mouseDoubleClickEvent(QMouseEvent *) {
	emit openProject(_path->text());
}
