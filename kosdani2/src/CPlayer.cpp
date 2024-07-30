/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 08.06.2023
 */

#include "CPlayer.h"
#include "constants.h"


using namespace std;

CPlayer &CPlayer::PurchaseTroop(size_t wave, size_t waves) {
    m_Interface.PrintTroopStore(m_Store.GetAvailableTroops(), m_Coins, wave, waves);
    size_t storesize = m_Store.GetAvailableTroops().size();
    while(true){
        size_t idx = m_Interface.PromptNumber();
        if(idx == storesize) {
            m_Ready = true;
            return *this;
        }
        if(idx > storesize) {
            m_Interface.PrintLine("Invalid number entered.");
            continue;
        }
        auto troop = m_Store.SellTroop(idx, m_Coins);
        if(!troop){
            m_Interface.PrintLine("Insufficient funds.");
            continue;
        }
        m_Coins -= troop->GetCost();
        m_PurchasedTroops.push_back(troop);
        return *this;
    }
}

std::shared_ptr<CTroop> CPlayer::DeployTroop(const CMap& map) {
    if(m_PurchasedTroops.empty())
        return nullptr;
    auto troop = m_PurchasedTroops.front();
    CCoord spawn = m_Interface.ChooseSpawn(map.GetSpawns(), troop->GetType());
    troop->SetSpawn(spawn);
    troop->FindPath(map);
    m_PurchasedTroops.pop_front();
    return troop;
}

size_t CPlayer::GetCoins() const {
    return m_Coins;
}

size_t CPlayer::GetScore() const {
    return m_Score;
}

CPlayer::CPlayer(CInterface &interface)
: m_Coins(0), m_Score(0), m_PurchasedTroops({}), m_Interface(interface) {}

CPlayer::CPlayer() : m_Coins(DEFAULT_COINS), m_Score(0), m_PurchasedTroops({}), m_Interface(cin, cout), m_Store() {}

CPlayer &CPlayer::AddScore(size_t score) {
    m_Score += score;
    return *this;
}

void CPlayer::ShowResult(bool won) {
    m_Interface.PrintResult(won, m_Score);
}

CPlayer &CPlayer::InitStore() {
    string file = m_Interface.PromptFilename("troop definitions");
    m_Store.AddTroops(file);
    return *this;
}

CPlayer &CPlayer::Prepare(size_t wave, const std::vector<std::vector<char>>& buffer, size_t health, size_t waves) {
    m_Coins += wave * DEFAULT_COINS;
    m_Ready = false;
    while(!m_Ready){
        m_Interface.FlushBuffer(buffer, health);
        PurchaseTroop(wave, waves);
    }
    return *this;
}
