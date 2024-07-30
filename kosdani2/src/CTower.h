/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 06.06.2023
 */

#pragma once

#include <cstddef>
#include <memory>
#include "CCoord.h"
#include "CTroop.h"

class CTower {
protected:
    size_t m_Damage;
    size_t m_Recharge; // nr of ticks between ability uses, 0 means ability every tick
    size_t m_Range;
    size_t m_AbilityCD;
    CCoord m_Coord;


public:
    CTower(size_t damage, size_t recharge, size_t range, size_t cd = 0);
    virtual void Ability(std::vector<std::shared_ptr<CTroop>> troops) = 0;
    CTower(const CTower&) = default;
    CTower& operator= (const CTower& ) = delete;
    virtual ~CTower() = default;
    virtual std::unique_ptr<CTower> Clone() const = 0;
    virtual char Print() const = 0;
    CCoord GetCoord() const;
    virtual std::string Description() const = 0;
    CTower& SetSpawn(const CCoord& spawn);
    size_t GetRange();
};
