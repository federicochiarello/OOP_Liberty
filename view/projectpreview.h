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

	const Controller* _controller;

	QVBoxLayout* _layout;

	QLabel* _name;
	QLabel* _path;

	void connects();

public:
	explicit ProjectPreview(QWidget* parent = nullptr);

	ProjectPreview(const Controller* controller, const QString& name, const QString& path, QWidget* parent =nullptr);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent*) override;
//	virtual void keyPressEvent(QKeyEvent* key) override;

signals:
	void openProject(const QString&);
};

#endif // PROJECTPREVIEW_H
