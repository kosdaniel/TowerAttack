/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include <vector>
#include <string>
#include "CCoord.h"
#include <map>
#include <deque>

class CMap {
private:
    size_t m_Height;
    size_t m_Width;
    std::vector<std::vector<bool>> m_Walls;
    CCoord m_Base;
    std::vector<CCoord> m_Spawns;
    size_t m_BaseHealth;
    std::map<CCoord, int> m_Heatmap;
    size_t m_Waves;
public:
    CMap();
    //CMap(size_t height = 0, size_t width = 0, std::vector<std::vector<bool>> walls = {}, CCoord base = {}, std::vector<CCoord> spawns = {}, size_t health = 0):m_Height(height), m_Width(width), m_Walls(std::move(walls)), m_Base(base), m_Spawns(std::move(spawns)), m_BaseHealth(health) {}
    explicit CMap(const std::string& file);
    std::vector<std::vector<char>> DrawMap() const;
    std::vector<std::vector<bool>> GetWalls() const;
    CCoord GetBase() const;
    std::map<CCoord, std::vector<CCoord>> MakeGraph() const;
    CMap& AttackBase();
    size_t GetBaseHealth() const;
    std::vector<CCoord> GetSpawns() const;
    std::deque<CCoord> FindAirPath(CCoord spawn) const;
    std::deque<CCoord> FindGroundPath(CCoord spawn) const;
    std::map<CCoord, int> GetHeatmap() const;
    size_t GetWaves() const;
    void PrintHeatmap();
};
