#include "controller.h"

Controller::Controller(Model* p_model, QObject* p_parent) : QObject(p_parent), m_model(p_model) {}

void Controller::setView(View *view) { m_view = view; }
