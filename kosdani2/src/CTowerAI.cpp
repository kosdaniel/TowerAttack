/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 10.06.2023
 */

#include <fstream>
#include <sstream>
#include "CTowerAI.h"
#include "CFreezeTower.h"
#include "CFireTower.h"
#include "CSniperTower.h"
#include "constants.h"


using namespace std;

CTowerAI::CTowerAI(CInterface &interface) : m_Interface(interface) {}

CTowerAI &CTowerAI::AddDefaultTowers() {
    m_TowerList.push_back(make_unique<CFreezeTower>(CFreezeTower(DEFAULT_FREEZE_DAMAGE, DEFAULT_FREEZE_RECHARGE, DEFAULT_FREEZE_RANGE)));
    m_TowerList.push_back(make_unique<CFireTower>(CFireTower(DEFAULT_FIRE_DAMAGE, DEFAULT_FIRE_RECHARGE, DEFAULT_FIRE_RANGE)));
    m_TowerList.push_back(make_unique<CSniperTower>(CSniperTower(DEFAULT_SNIPER_DAMAGE, DEFAULT_SNIPER_RECHARGE, DEFAULT_SNIPER_RANGE)));
    return *this;
}

CTowerAI &CTowerAI::AddTowers(const string &file) {
    if(file.empty()){
        AddDefaultTowers();
        return *this;
    }
    string line;
    ifstream inFile(file);
    if(!inFile.is_open() || !inFile)
        throw runtime_error("Cannot open tower definition file");
    string type;
    size_t damage, recharge, range;
    while(getline(inFile, line)){
        istringstream iss(line);
        if(!(iss >> type))
            throw runtime_error("Invalid tower definition file format");
        if(type == "CFreezeTower"){
            if(!(iss >> damage >> range >> recharge))
                throw runtime_error("Invalid tower definition file format");
            m_TowerList.push_back(make_unique<CFreezeTower>(CFreezeTower(damage, recharge, range)));
        }
        else if(type == "CSniperTower"){
            if(!(iss >> damage >> range >> recharge))
                throw runtime_error("Invalid tower definition file format");
            m_TowerList.push_back(make_unique<CSniperTower>(CSniperTower(damage, recharge, range)));
        }
        else if(type == "CFireTower"){
            if(!(iss >> damage >> range >> recharge))
                throw runtime_error("Invalid tower definition file format");
            m_TowerList.push_back(make_unique<CFireTower>(CFireTower(damage, recharge, range)));
        }
        else throw runtime_error("Unknown tower type in tower definition file");
    }
    return *this;
}

CTowerAI &CTowerAI::Init() {
    string file = m_Interface.PromptFilename("tower definitions");
    return AddTowers(file);
}



const std::vector<std::unique_ptr<CTower>> &CTowerAI::GetTowerList() const {
    return m_TowerList;
}

