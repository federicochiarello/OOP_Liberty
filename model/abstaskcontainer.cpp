#include "abstaskcontainer.h"

AbsTaskContainer::AbsTaskContainer() {}

std::vector<AbsTask *> AbsTaskContainer::getChilds() const {
    return m_child;
}

// warning per la perdita del const
void AbsTaskContainer::addChild(const AbsTask * p_child) {
    m_child.push_back(p_child);
}

void AbsTaskContainer::removeChild(const AbsTask * p_child) {
    std::vector<AbsTask*>::iterator i = m_child.begin();
    bool trovato = false;
    while(trovato == false && i != m_child.end()){
        if (*i == p_child) {
            m_child.erase(i);
            trovato = true;
        }
        i++;
    }
}
