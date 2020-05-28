#include "textholder.h"

TextHolder::TextHolder(QWidget* parent) : QTextEdit(parent) {
	setup();
}

TextHolder::TextHolder(const QString& text, QWidget* parent) : QTextEdit(text, parent) {
	setup();
}


void TextHolder::setup() {
	setEnabled(true);
	setMinimumSize(100, 30);
	//setMaximumSize(275, 200);
	setGeometry(0, 0, 150, 30);
	setSizePolicy(QSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed));
}

/*
void TextHolder::mousePressEvent(QMouseEvent* e) {
	if (e->button() == Qt::LeftButton) {

	}
}
*/
