#ifndef TPREVIEW_H
#define TPREVIEW_H

#include <QApplication>
#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QToolButton>
#include <QMouseEvent>

#include "textholder.h"
#include "taskwidget.h"

class TPreview : public QWidget {
	Q_OBJECT
public:
	explicit TPreview(QWidget *parent = nullptr);

protected:
	virtual void mouseDoubleClickEvent(QMouseEvent *event) override;

	//virtual void mousePressEvent(QMouseEvent *event) override;
	//virtual void mouseMoveEvent(QMouseEvent *event) override;

private:
	QHBoxLayout* _layout;

	//QPoint dragStartPos;
	void setup();
};

#endif // TPREVIEW_H
