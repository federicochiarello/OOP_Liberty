#include "projectpreview.h"

void ProjectPreview::connects() {
	connect(this, SIGNAL(openProject(const QString&)),
			_controller, SLOT(onOpenProject(const QString&)));
}

ProjectPreview::ProjectPreview(QWidget *parent) : QWidget(parent) {
	//QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_F2),this, SIGNAL(getText));
	//shortcut->setAutoRepeat(false);
}

ProjectPreview::ProjectPreview(const Controller* controller, const QString& name, const QString& pathToDir, QWidget *parent) :
	QWidget(parent),
	_controller(controller),
	_layout(new QVBoxLayout(this)),
	_name(new QLabel(name, this)),
	_path(new QLabel(pathToDir+"/"+name, this)) {

	connects();

	_layout->addWidget(_name);
	_layout->addWidget(_path);
}

void ProjectPreview::mouseDoubleClickEvent(QMouseEvent *) {
	emit openProject(_path->text());
}

//void ProjectPreview::keyPressEvent(QKeyEvent* event) {
//	QLineEdit::keyPressEvent(event);
//	if (event->key() ==	Qt::Key_Enter) {
//		//emit newList();
//	}
//}


//std::string ProjectPreview::newList() {
//	return text().toStdString();
//}

