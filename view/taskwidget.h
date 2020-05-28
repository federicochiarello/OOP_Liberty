#ifndef TASKWIDGET_H
#define TASKWIDGET_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QTextEdit>
#include <QToolButton>

#include "textholder.h"

class TaskWidget : public QWidget {
	Q_OBJECT
public:
	explicit TaskWidget(QWidget* parent =nullptr);
	TaskWidget(const TaskWidget& widget,QWidget* parent =nullptr);
	TaskWidget(const QString& title, const QString& desc =QString(), QWidget* parent =nullptr);

	void setName();
	void setDesc();
	void generateLayout();

	static QSize minSize;
	static QSize maxSize;
protected:
	//void mousePressEvent(QMouseEvent *event) override;
private:
	QVBoxLayout*	_layout;
	QTextEdit*			_title;
	QTextEdit*			_desc;

	void setup();
};

#endif // TASKWIDGET_H
