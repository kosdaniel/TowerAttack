/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 04.06.2023
 */

#pragma once


#include <vector>
#include <memory>
#include "CTower.h"
#include "CMap.h"
#include "CTroop.h"
#include "CPlayer.h"
#include "CTowerAI.h"

class CGame {
private:
    std::vector<std::shared_ptr<CTower>> m_Towers;
    std::vector<std::shared_ptr<CTroop>> m_Troops;
    CMap m_Map;
    std::unique_ptr<CPlayer> m_Player;
    std::unique_ptr<CTowerAI> m_TowerAI;
    std::deque<std::shared_ptr<CTroop>> m_Queue;
    bool m_Ended = false;
    bool m_WaveFinished = false;
    CInterface m_Interface;
    size_t m_Wave = 1;
public:
    explicit CGame(std::unique_ptr<CPlayer> player, std::unique_ptr<CTowerAI> ai, CInterface interface);
    CGame& Initialize();
    CGame& Update();
    std::vector<std::vector<char>> DrawGame();
    CGame& End();
    void Run();
    CGame& DeployTowers(const std::vector<std::unique_ptr<CTower>>& towers);
    CGame& BuildTower(const std::shared_ptr<CTower>& tower);
    CCoord FindOptimalSpawn(size_t range);
    int SumPaths(CCoord spawn, size_t range);
};








