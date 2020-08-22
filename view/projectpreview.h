#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QLineEdit>
#include <QKeyEvent>
#include <QShortcut>

class ProjectPreview : public QLineEdit {
	Q_OBJECT
public:
	explicit ProjectPreview(QWidget* parent = nullptr);

	virtual void keyPressEvent(QKeyEvent* key) override;
signals:
	//std::string newList();
};

#endif // PROJECTPREVIEW_H
