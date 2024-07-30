/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 06.06.2023
 */

#include "CFreezeTower.h"

using namespace std;

void CFreezeTower::Ability(std::vector<std::shared_ptr<CTroop>> troops) {
    if(m_AbilityCD > 0){
        m_AbilityCD--;
        return;
    }
    bool used = false;
    for(const auto& troop : troops){
        if(Distance(m_Coord, troop->GetCoord()) <= m_Range){
            troop->GetFrozen(m_Damage);
            used = true;
        }
    }
    if(used)
        m_AbilityCD += m_Recharge;
}

char CFreezeTower::Print() const {
    return '*';
}

std::string CFreezeTower::Description() const {
    return "Freeze tower: freeze all troops in range for -m_Damage- ticks. ";
}

std::unique_ptr<CTower> CFreezeTower::Clone() const {
    return make_unique<CFreezeTower>(*this);
}

CFreezeTower::CFreezeTower(size_t damage, size_t recharge, size_t range) : CTower(damage, recharge, range) {}
