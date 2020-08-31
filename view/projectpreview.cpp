#include "projectpreview.h"

void ProjectPreview::connects() {
	connect(this, SIGNAL(openProject(const QString&)),
			_controller, SLOT(onOpenProject(const QString&)));
}

ProjectPreview::ProjectPreview(QWidget *parent) : QWidget(parent) {
	//QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_F2),this, SIGNAL(getText));
	//shortcut->setAutoRepeat(false);
}

ProjectPreview::ProjectPreview(const QString& name, const QString& pathToDir, const Controller* controller, QWidget *parent) :
	_name(name),
	_path(pathToDir+"/"+name),
	_controller(controller) {

	QVBoxLayout* layout = new QVBoxLayout();

	if (layout) {
		layout->addWidget(new QLabel(_name, this));
		layout->addWidget(new QLabel(_path, this));
	}
	setLayout(layout);
}

void ProjectPreview::mouseDoubleClickEvent(QMouseEvent *) {
	emit openProject(_name);
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

