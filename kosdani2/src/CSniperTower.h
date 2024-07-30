/**
 * @author Daniel Kos <kosdani@fit.cvut.cz>
 * @date 06.06.2023
 */

#pragma once


#include "CTower.h"

class CSniperTower : public CTower {
public:
    CSniperTower(size_t damage, size_t recharge, size_t range);
    void Ability(std::vector<std::shared_ptr<CTroop>> troops) override;
    char Print() const override;
    std::string Description() const override;
    std::unique_ptr<CTower> Clone() const override;
};
