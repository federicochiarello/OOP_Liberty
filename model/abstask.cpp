#include "abstask.h"

AbsTask::AbsTask(AbsTask* p_parent) : m_parent(p_parent) {}

AbsTask::AbsTask(const std::string p_label, AbsTask* p_parent) : m_label(p_label), m_parent(p_parent) {}

AbsTask::AbsTask(const AbsTask& p_el, AbsTask* p_parent) : m_label(p_el.m_label), m_parent(p_parent) {}
