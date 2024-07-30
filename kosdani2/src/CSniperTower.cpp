/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 06.06.2023
 */

#include <algorithm>
#include "CSniperTower.h"

using namespace std;

void CSniperTower::Ability(std::vector<std::shared_ptr<CTroop>> troops) {
    if(m_AbilityCD > 0){
        m_AbilityCD--;
        return;
    }
    auto toHit = min_element(troops.begin(), troops.end(),
                             [this](const shared_ptr<CTroop>& a, const shared_ptr<CTroop>& b){
                             return Distance(m_Coord, a->GetCoord()) < Distance(m_Coord, b->GetCoord());});
    if(toHit != troops.end() && Distance((*toHit)->GetCoord(), m_Coord) <= m_Range) {
        (*toHit)->TakeDamage(m_Damage);
        m_AbilityCD += m_Recharge;
    }
}

char CSniperTower::Print() const {
    return 'i';
}

std::string CSniperTower::Description() const {
    return "Sniper tower: deals -m_Attack- damage to a single closest troop";
}

std::unique_ptr<CTower> CSniperTower::Clone() const {
    return make_unique<CSniperTower>(*this);
}

CSniperTower::CSniperTower(size_t damage, size_t recharge, size_t range) : CTower(damage, recharge, range) {}

