#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>

#include "view/view.h"
//#include "model/model.h"

class Model;

class Controller : public QObject {
	Q_OBJECT

	Model* _model;
	View* _view;

public:
	explicit Controller(Model* model);

	void setView(View* view);

public slots:
	void sendTaskData(const unsigned short);
signals:

};

#endif // CONTROLLER_H
