#ifndef PROJECTPREVIEW_H
#define PROJECTPREVIEW_H

#include <QWidget>
#include <QLayout>
#include <QLineEdit>
#include <QLabel>
#include <QKeyEvent>
#include <QShortcut>

class ProjectPreview : public QWidget {
	Q_OBJECT

//	const unsigned short _id;
	QString _name;
	QString _path;

public:
	explicit ProjectPreview(QWidget* parent = nullptr);

	ProjectPreview(QString name, QString path =QString(), QWidget* parent =nullptr);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent*) override;
//	virtual void keyPressEvent(QKeyEvent* key) override;

signals:
	void openProject(QString);
};

#endif // PROJECTPREVIEW_H
