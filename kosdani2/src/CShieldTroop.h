/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include "CGroundTroop.h"

class CShieldTroop : public CGroundTroop {
private:
    size_t m_ShieldCount;
public:
    CShieldTroop(size_t shield, size_t speed, size_t health, size_t cost);
    CTroop& TakeDamage(size_t damage) override;
    char Print() const override;
    std::unique_ptr<CTroop> Clone() const override;
    void Description(std::ostream& out) const override;
    std::string GetType() const override;

};
