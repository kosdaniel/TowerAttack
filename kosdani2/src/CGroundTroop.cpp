/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include <set>
#include <map>
#include <deque>
#include "CGroundTroop.h"


using namespace std;

void CGroundTroop::FindPath(const CMap &Map) {
    /*CCoord base = Map.GetBase();
    map<CCoord, vector<CCoord>> graph = Map.MakeGraph();
    set<CCoord> visited;
    deque<CCoord> queue;
    visited.insert(m_Coord);
    queue.push_back(m_Coord);
    map<CCoord, CCoord> edges;
    while(!queue.empty()){
        CCoord cur = queue.front();
        queue.pop_front();
        if(cur == base)
            break;
        for(CCoord adj : graph[cur]){
            if(!visited.count(adj)){
                visited.insert(adj);
                queue.push_back(adj);
                edges[adj] = cur;
            }
        }
    }
    if(!visited.count(base))
        throw runtime_error("Invalid map - ground path from spawn to base does not exist");
    deque<CCoord> path;
    path.push_back(base);
    CCoord cur = base;
    while(edges.count(cur)){
        cur = edges[cur];
        path.push_front(cur);
    }

    m_Path = path;*/

    m_Path = Map.FindGroundPath(m_Coord);
}

char CGroundTroop::Print() const {
    return 'a';
}

CGroundTroop::CGroundTroop(size_t speed, size_t health, size_t cost) : CTroop(
        speed, health, cost) {
}

std::unique_ptr<CTroop> CGroundTroop::Clone() const {
    return make_unique<CGroundTroop>(*this);
}

void CGroundTroop::Description(ostream &out) const {
    out << "Ground troop. HP:" << m_Health << " Speed:" << m_Speed << " Cost:" << m_Cost;
}

std::string CGroundTroop::GetType() const {
    return "Ground Troop";
}
