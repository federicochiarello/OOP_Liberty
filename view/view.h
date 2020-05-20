#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>
#include <QLayout>
#include <QMenuBar>

class View : public QWidget {
	Q_OBJECT
private:
	QVBoxLayout* mainLayout;
public:
	View(QWidget* parent =nullptr);
	void createMenu();
};

#endif // VIEW_H
