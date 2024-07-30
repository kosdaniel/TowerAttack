/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include "CTower.h"

class CFireTower : public CTower {
public:
    CFireTower(size_t damage, size_t recharge, size_t range);
    void Ability(std::vector<std::shared_ptr<CTroop>> troops) override;
    char Print() const override;
    std::string Description() const override;
    std::unique_ptr<CTower> Clone() const override;
};
