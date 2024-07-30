/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include "CTroop.h"


using namespace std;

CCoord CTroop::GetCoord() const {
    return m_Coord;
}

CTroop& CTroop::TakeDamage(size_t damage) {
    (m_Health <= damage)? m_Health = 0 : m_Health -= damage;
    return *this;
}

size_t CTroop::GetCost() const {
    return m_Cost;
}

CTroop& CTroop::Move() {
    if(m_MoveCD > 0){
        m_MoveCD--;
        return *this;
    }
    m_Coord = m_Path.front();
    m_Path.pop_front();
    m_MoveCD += m_Speed;
    return *this;
}

CTroop &CTroop::GetFrozen(size_t cooldown) {
    m_MoveCD += cooldown;
    return *this;
}

size_t CTroop::GetHealth() const {
    return m_Health;
}

CTroop::CTroop(size_t speed, size_t health, size_t cost, size_t cd)
: m_Speed(speed), m_Health(health), m_Cost(cost), m_MoveCD(cd) {}

std::ostream &operator<<(ostream &out, const CTroop &troop) {
    troop.Description(out);
    return out;
}

CTroop &CTroop::SetSpawn(CCoord spawn) {
    m_Coord = spawn;
    return *this;
}

std::deque<CCoord> CTroop::GetPath() const {
    return m_Path;
}
