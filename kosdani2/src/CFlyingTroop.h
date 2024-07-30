/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include "CMap.h"
#include "CTroop.h"

class CFlyingTroop : public CTroop {
public:
    CFlyingTroop(size_t speed, size_t health,size_t cost);
    void FindPath(const CMap& map) override;
    char Print() const override;
    std::unique_ptr<CTroop> Clone() const override;
    void Description(std::ostream& out) const override;
    std::string GetType() const override;
};
