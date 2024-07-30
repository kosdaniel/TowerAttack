/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include <cstdlib>
#include <iostream>
#include <vector>
#include <memory>
#include <deque>
#include "CCoord.h"
#include "CMap.h"

class CTroop {
protected:
    size_t m_Speed; //defined as nr of ticks between every Move(). max speed: 0
    size_t m_Health;
    size_t m_Cost;
    size_t m_MoveCD;
    CCoord m_Coord;
    std::deque<CCoord> m_Path;
public:
    CTroop(size_t speed, size_t health,size_t cost, size_t cd = 0);
    CTroop(const CTroop&) = default;
    virtual void FindPath(const CMap& map) = 0;
    CTroop& Move();
    CCoord GetCoord() const;
    virtual CTroop& TakeDamage(size_t damage);
    virtual CTroop& GetFrozen(size_t cooldown);
    virtual ~CTroop() = default;
    virtual std::unique_ptr<CTroop> Clone() const = 0;
    size_t GetCost() const;
    size_t GetHealth() const;
    virtual char Print() const = 0;
    virtual void Description(std::ostream& out) const = 0;
    friend std::ostream& operator <<(std::ostream& out, const CTroop& troop);
    CTroop& SetSpawn(CCoord spawn);
    virtual std::string GetType() const = 0;
    std::deque<CCoord> GetPath() const;
};


