/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 08.06.2023
 */

#pragma once


#include "CInterface.h"
#include "CTroop.h"

class CPlayer {
private:
    size_t m_Coins;
    size_t m_Score;
    std::deque<std::shared_ptr<CTroop>> m_PurchasedTroops;
    CInterface m_Interface;
    CTroopStore m_Store;
    bool m_Ready = false;
public:
    explicit CPlayer(CInterface& interface);
    CPlayer();
    size_t GetCoins() const;
    size_t GetScore() const;
    CPlayer& PurchaseTroop(size_t wave, size_t waves);
    std::shared_ptr<CTroop> DeployTroop(const CMap& map);
    CPlayer& Prepare(size_t wave, const std::vector<std::vector<char>>& buffer, size_t health, size_t waves);
    CPlayer& AddScore(size_t score);
    void ShowResult(bool won);
    CPlayer& InitStore();
};


//make armored plane, combine tower effects, define default towers, make tower file config, make tower AI, make save/load game