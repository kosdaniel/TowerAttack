/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 04.06.2023
 */

#include <algorithm>
#include <chrono>
#include <thread>
#include "CGame.h"
#include "constants.h"

using namespace std;

std::vector<std::vector<char>> CGame::DrawGame() {
    vector<vector<char>> buffer = m_Map.DrawMap();
    for(const auto& tower : m_Towers){
        buffer[tower->GetCoord().m_Y][tower->GetCoord().m_X] = tower->Print();
    }
    for(const auto& troop : m_Troops){
        buffer[troop->GetCoord().m_Y][troop->GetCoord().m_X] = troop->Print();
    }
    return buffer;
}


CGame &CGame::Update() {
    for(auto& tower: m_Towers)
        tower->Ability(m_Troops);
    /*m_Troops.erase(remove_if(m_Troops.begin(), m_Troops.end(),
                             [](const shared_ptr<CTroop>& t)
                             {return t->GetHealth() == 0;}), m_Troops.end());*/
    for(auto troopIt = m_Troops.begin(); troopIt != m_Troops.end();){
        if((*troopIt)->GetHealth() == 0){
            troopIt = m_Troops.erase(troopIt);
            continue;
        }
        (*troopIt)->Move();
        if((*troopIt)->GetCoord() == m_Map.GetBase()){
            m_Map.AttackBase();
            m_Player->AddScore(DEFAULT_ATK_SCORE);
            troopIt = m_Troops.erase(troopIt);
            if(m_Map.GetBaseHealth() == 0){
                m_WaveFinished = true;
                break;
            }
        }
        else ++troopIt;
    }
    auto newTroop = m_Player->DeployTroop(m_Map);
    if(newTroop != nullptr)
        m_Troops.push_back(newTroop);
    else
        //m_Interface.Continue();
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    /*if(!m_Queue.empty()){
        m_Troops.push_back(m_Queue.front());
        m_Queue.pop_front();
    }*/
    if(m_Troops.empty())
        m_WaveFinished = true;
    return *this;
}

CGame &CGame::End() {
    if(m_Map.GetBaseHealth() == 0){
        m_Player->AddScore(m_Player->GetCoins() * DEFAULT_COINS_MULTIPLIER);
        m_Player->AddScore((m_Map.GetWaves() - m_Wave) * DEFAULT_WAVE_BONUS);
        m_Player->ShowResult(true);
    }
    else
        m_Player->ShowResult(false);
    return *this;
}

void CGame::Run() {
    while(!m_Ended) {
        m_Troops.clear();
        DeployTowers(m_TowerAI->GetTowerList());
        m_Player->Prepare(m_Wave, DrawGame(), m_Map.GetBaseHealth(), m_Map.GetWaves());
        m_Interface.FlushBuffer(DrawGame(), m_Map.GetBaseHealth());
        m_WaveFinished = false;
        while (!m_WaveFinished) {
            Update();
            m_Interface.FlushBuffer(DrawGame(), m_Map.GetBaseHealth());
        }
        m_Wave++;
        if(m_Wave > m_Map.GetWaves() || m_Map.GetBaseHealth() == 0)
            m_Ended = true;
    }
    End();
}

CGame &CGame::Initialize() {
    m_Map = CMap(m_Interface.PromptFilename("map"));
    //m_Map.PrintHeatmap();
    m_TowerAI->Init();
    m_Player->InitStore();
    return *this;
}



CGame::CGame(unique_ptr<CPlayer> player, unique_ptr<CTowerAI> ai, CInterface interface)
 : m_Player(move(player)), m_TowerAI(move(ai)), m_Interface(interface) {}

CGame &CGame::DeployTowers(const vector<std::unique_ptr<CTower>> &towers) {
    for (const auto &tower: towers) {
        BuildTower(tower->Clone());
    }
    return *this;
}

CGame &CGame::BuildTower(const std::shared_ptr<CTower>& tower) {
    CCoord towerSpawn = FindOptimalSpawn(tower->GetRange());
    tower->SetSpawn(towerSpawn);
    m_Towers.push_back(tower);
    return *this;
}

CCoord CGame::FindOptimalSpawn(size_t range) {
    std::vector<std::vector<bool>> walls = m_Map.GetWalls();
    for(const auto& tower : m_Towers){
        walls[tower->GetCoord().m_Y][tower->GetCoord().m_X] = false;
    }
    std::map<CCoord, int> heatmap = m_Map.GetHeatmap();
    CCoord spawn(0, 0);
    int sum, curScore = 0;
    for(int h = 0; h < (int)walls.size(); h++)
        for(int w = 0; w < (int)walls[h].size(); w++){
            if(!walls[h][w])
                continue;
            sum = SumPaths(CCoord(w, h),range);
            if(sum > curScore){
                curScore = sum;
                spawn = CCoord(w, h);
            }
        }
    return spawn;
}

int CGame::SumPaths(CCoord spawn, size_t range) {
    int score = 0;
    for(const auto& tile : m_Map.GetHeatmap()){
        if(Distance(tile.first, spawn) <= range)
            score += tile.second;
    }
    return score;
}




