#ifndef TASKPREVIEW_H
#define TASKPREVIEW_H

#include <QApplication>
#include <QObject>
#include <QLineEdit>
#include <QLayout>
#include <QMouseEvent>

#include "textholder.h"
#include "taskwidget.h"

class TaskPreview : public QLineEdit {
	Q_OBJECT

	unsigned short _id;
public:
	explicit TaskPreview(QWidget* parent = nullptr);
	explicit TaskPreview(int id, QWidget* parent = nullptr);
	explicit TaskPreview(QString taskName, int id, QWidget* parent = nullptr);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* event) override;

	//virtual void mousePressEvent(QMouseEvent *event) override;
	//virtual void mouseMoveEvent(QMouseEvent *event) override;

public slots:
	void setTaskName(std::string);

signals:
	void openTaskInfo(unsigned short);
	void changedTaskName(unsigned short, std::string);

};

#endif // TASKPREVIEW_H
