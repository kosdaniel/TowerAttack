/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 06.06.2023
 */

#include "CTower.h"

CCoord CTower::GetCoord() const {
    return m_Coord;
}

CTower::CTower(size_t damage, size_t recharge, size_t range, size_t cd)
: m_Damage(damage), m_Recharge(recharge), m_Range(range), m_AbilityCD(cd) {}

CTower &CTower::SetSpawn(const CCoord &spawn) {
    m_Coord = spawn;
    return *this;
}

size_t CTower::GetRange() {
    return m_Range;
}


