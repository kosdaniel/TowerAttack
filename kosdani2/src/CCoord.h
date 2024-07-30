/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 06.06.2023
 */

#pragma once


#include <cstdlib>
#include <cmath>

struct CCoord {
    int m_X;
    int m_Y;
    CCoord(int x, int y) : m_X(x), m_Y(y) {}
    CCoord() = default;
};

size_t Distance(const CCoord& a, const CCoord& b);
bool operator< (const CCoord& a, const CCoord& b);
bool operator== (const CCoord& a, const CCoord& b);
bool operator!= (const CCoord& a, const CCoord& b);
