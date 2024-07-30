/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include "CShieldTroop.h"


using namespace std;

CTroop &CShieldTroop::TakeDamage(size_t damage) {
    if(m_ShieldCount > 0){
        m_ShieldCount--;
        return *this;
    }
    return CTroop::TakeDamage(damage);
}

char CShieldTroop::Print() const {
    return '@';
}

CShieldTroop::CShieldTroop(size_t shield, size_t speed, size_t health, size_t cost) :
CGroundTroop(speed, health, cost), m_ShieldCount(shield) {}

std::unique_ptr<CTroop> CShieldTroop::Clone() const {
    return make_unique<CShieldTroop>(*this);
}

void CShieldTroop::Description(ostream &out) const {
    out << "Shield troop. HP:" << m_Health << " Speed:" << m_Speed << " Shield charges:" << m_ShieldCount << " Cost:" << m_Cost;
}

std::string CShieldTroop::GetType() const {
    return "Shield Troop";
}
