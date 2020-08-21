#include "controller.h"

Controller::Controller(Model* model) : _model(model) {
	connect(_view, SIGNAL(), this, SLOT(sendTaskData(const unsigned short)));
}

void Controller::setView(View *view) { _view = view; }

void Controller::sendTaskData(const unsigned short) {

}
