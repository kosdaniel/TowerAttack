/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include "CFireTower.h"


using namespace std;

void CFireTower::Ability(std::vector<std::shared_ptr<CTroop>> troops) {
    if(m_AbilityCD > 0){
        m_AbilityCD--;
        return;
    }
    bool used = false;
    for(const auto& troop : troops){
        if(Distance(m_Coord, troop->GetCoord()) <= m_Range){
            troop->TakeDamage(m_Damage);
            used = true;
        }
    }
    if(used)
        m_AbilityCD += m_Recharge;
}

char CFireTower::Print() const {
    return '$';
}

std::string CFireTower::Description() const {
    return "Fire tower: deals -m_Attack- damage to all troops in range.";
}

std::unique_ptr<CTower> CFireTower::Clone() const {
    return make_unique<CFireTower>(*this);
}

CFireTower::CFireTower(size_t damage, size_t recharge, size_t range) : CTower(damage, recharge, range) {}
