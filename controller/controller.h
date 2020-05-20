#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "view/view.h"
#include "model/model.h"

class Controller : public QObject {
	Q_OBJECT

public:
	Controller(Model* model, QObject* parent =nullptr);

	void setView(View* view);
private:
	View* m_view;
	Model* m_model;
};

#endif // CONTROLLER_H
