#include "projectpreview.h"

ProjectPreview::ProjectPreview(QWidget *parent) : QLineEdit(parent) {
	//QShortcut * shortcut = new QShortcut(QKeySequence(Qt::Key_F2),this, SIGNAL(getText));
	//shortcut->setAutoRepeat(false);
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

