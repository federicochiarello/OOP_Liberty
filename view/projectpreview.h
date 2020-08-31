#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QShortcut>

#include "controller/controller.h"

class ProjectPreview : public QWidget {
	Q_OBJECT

	const QString _name;
	const QString _path;
	const Controller* _controller;

	void connects();

public:
	explicit ProjectPreview(QWidget* parent = nullptr);

	ProjectPreview(const QString& name, const QString& path, const Controller* controller, QWidget* parent =nullptr);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent*) override;
//	virtual void keyPressEvent(QKeyEvent* key) override;

signals:
	void openProject(const QString&);
};

#endif // PROJECTPREVIEW_H
