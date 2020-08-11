#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "view/view.h"
//#include "model/model.h"

class Model;

class Controller {
	Model* _model;
	View* _view;

public:
	Controller();
};

#endif // CONTROLLER_H
