/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 06.06.2023
 */

#include <tuple>
#include "CCoord.h"

using namespace std;

bool operator<(const CCoord &a, const CCoord &b) {
    return std::tie(a.m_X, a.m_Y) < std::tie(b.m_X, b.m_Y);
}

size_t Distance(const CCoord &a, const CCoord &b) {
    return (size_t)sqrt(pow((double)(b.m_X - a.m_X),2) + pow((double)(b.m_Y - a.m_Y),2));
}

bool operator==(const CCoord &a, const CCoord &b) {
    return a.m_X == b.m_X && a.m_Y == b.m_Y;
}

bool operator!=(const CCoord &a, const CCoord &b) {
    return !(a==b);
}
