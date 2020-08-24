#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QShortcut>

class ProjectPreview : public QLineEdit {
	Q_OBJECT

//	const unsigned short _id;
	QLineEdit _name;
	QLabel _path;

public:
	explicit ProjectPreview(QWidget* parent = nullptr);

//	virtual void keyPressEvent(QKeyEvent* key) override;
signals:
//	std::string newList();
};

#endif // PROJECTPREVIEW_H
