/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include "CFlyingTroop.h"
#include <cmath>


using namespace std;

void CFlyingTroop::FindPath(const CMap &map) {
    /*CCoord base = map.GetBase();
    deque<CCoord> path;
    CCoord cur = m_Coord;
    while(cur != base){
        if(abs((int)(cur.m_X - base.m_X)) > abs((int)(cur.m_Y - base.m_Y)))
            cur.m_X > base.m_X ? cur.m_X -= 1 : cur.m_X += 1;
        else
            cur.m_Y > base.m_Y ? cur.m_Y -= 1 : cur.m_Y += 1;
        path.push_back(cur);
    }
    m_Path = path;*/
    m_Path = map.FindAirPath(m_Coord);
}

char CFlyingTroop::Print() const {
    return '^';
}

CFlyingTroop::CFlyingTroop(size_t speed, size_t health, size_t cost) : CTroop(
        speed, health, cost) {
}

std::unique_ptr<CTroop> CFlyingTroop::Clone() const {
    return make_unique<CFlyingTroop>(*this);
}

void CFlyingTroop::Description(ostream &out) const {
    out << "Flying troop. HP:" << m_Health << " Speed:" << m_Speed << " Cost:" << m_Cost;
}

std::string CFlyingTroop::GetType() const {
    return "Flying Troop";
}
