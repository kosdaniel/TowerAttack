/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 09.06.2023
 */

#include "CTroopStore.h"
#include <fstream>
#include <sstream>
#include "CGroundTroop.h"
#include "CFlyingTroop.h"
#include "CShieldTroop.h"
#include "constants.h"


using namespace std;

CTroopStore &CTroopStore::AddTroop(std::unique_ptr<CTroop> troop) {
    m_AvailableTroops.push_back(move(troop));
    return *this;
}


CTroopStore &CTroopStore::AddTroops(const string &file) {
    if(file.empty()){
        AddDefaultTroops();
        return *this;
    }
    string line;
    ifstream inFile(file);
    if(!inFile.is_open() || !inFile)
        throw runtime_error("Cannot open troop definition file");
    string type;
    size_t speed, health, cost, shield;
    while(getline(inFile, line)){
        istringstream iss(line);
        if(!(iss >> type))
            throw runtime_error("Invalid troop definition file format");
        if(type == "CGroundTroop"){
            if(!(iss >> speed >> health >> cost))
                throw runtime_error("Invalid troop definition file format");
            //m_AvailableTroops.push_back(CGroundTroop(speed, health, cost).Clone());
            m_AvailableTroops.push_back(make_unique<CGroundTroop>(CGroundTroop(speed, health, cost)));
        }
        else if(type == "CFlyingTroop"){
            if(!(iss >> speed >> health >> cost))
                throw runtime_error("Invalid troop definition file format");
            //m_AvailableTroops.push_back(CFlyingTroop(speed, health, cost).Clone());
            m_AvailableTroops.push_back(make_unique<CFlyingTroop>(CFlyingTroop(speed, health, cost)));
        }
        else if(type == "CShieldTroop"){
            if(!(iss >> speed >> health >> cost >> shield))
                throw runtime_error("Invalid troop definition file format");
            //m_AvailableTroops.push_back(CShieldTroop(shield, speed, health, cost).Clone());
            m_AvailableTroops.push_back(make_unique<CShieldTroop>(CShieldTroop(shield, speed, health, cost)));
        }
        else throw runtime_error("Unknown troop type in troop definition file");
    }
    return *this;
}

std::shared_ptr<CTroop> CTroopStore::SellTroop(size_t idx, size_t coins) {
    auto newTroop = m_AvailableTroops[idx]->Clone();
    if(newTroop->GetCost() > coins)
        return nullptr;
    return newTroop;
}


CTroopStore &CTroopStore::AddDefaultTroops() {
    m_AvailableTroops.push_back(CGroundTroop(DEFAULT_GROUND_SPEED, DEFAULT_GROUND_HP, DEFAULT_GROUND_COST).Clone());
    m_AvailableTroops.push_back(CFlyingTroop(DEFAULT_FLYING_SPEED, DEFAULT_FLYING_HP, DEFAULT_FLYING_COST).Clone());
    m_AvailableTroops.push_back(CShieldTroop(DEFAULT_SHIELD_SHIELD, DEFAULT_SHIELD_SPEED, DEFAULT_SHIELD_HP, DEFAULT_SHIELD_COST).Clone());
    return *this;
}

const std::vector<std::unique_ptr<CTroop>> &CTroopStore::GetAvailableTroops() const {
    return m_AvailableTroops;
}




