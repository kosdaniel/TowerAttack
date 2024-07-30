/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 09.06.2023
 */

#pragma once


#include "CTroop.h"
#include "CInterface.h"

class CTroopStore {
private:
    std::vector<std::unique_ptr<CTroop>> m_AvailableTroops;
public:
    CTroopStore() = default;
    CTroopStore& AddDefaultTroops();
    CTroopStore& AddTroop(std::unique_ptr<CTroop> troop);
    CTroopStore& AddTroops(const std::string& file);
    std::shared_ptr<CTroop> SellTroop(size_t idx, size_t coins);
    const std::vector<std::unique_ptr<CTroop>>& GetAvailableTroops() const;
};
