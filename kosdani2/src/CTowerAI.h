/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 10.06.2023
 */

#pragma once


#include "CTower.h"
#include "CInterface.h"

class CTowerAI {
private:
    std::vector<std::unique_ptr<CTower>> m_TowerList;
    CInterface m_Interface;
public:
    explicit CTowerAI(CInterface& interface);
    CTowerAI& AddTowers(const std::string& file);
    CTowerAI& AddDefaultTowers();
    CTowerAI& Init();
    const std::vector<std::unique_ptr<CTower>>& GetTowerList() const;
};
