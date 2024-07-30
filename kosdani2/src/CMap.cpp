/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include <fstream>
#include <deque>
#include "CMap.h"
#include "constants.h"
#include <set>
#include <iostream>

using namespace std;

CMap::CMap(const std::string &file) {
    string filename = file;
    if(file.empty())
        filename = DEFAULT_MAP;
    ifstream inFile(filename);
    if(!inFile.is_open() || !inFile)
        throw runtime_error("Cannot open map file");
    size_t width, height, health, waves;
    vector<CCoord> spawns;
    CCoord base{};
    bool gotBase = false;
    int c;
    if(!(inFile >> width >> height >> health >> waves) || inFile.get() != '\n')
        throw runtime_error("Incorrect map file format");
    width += 2;
    height += 2;
    vector<vector<bool>> walls(height, vector<bool>(width,false));
    for(size_t w = 0; w < width; w++){
        walls[0][w] = true;
        walls[height - 1][w] = true;
    }
    for(size_t h = 0; h < height; h++){
        walls[h][0] = true;
        walls[h][width - 1] = true;
    }

    for(size_t h = 1; h < height - 1; h++){
        for(size_t w = 1; w < width - 1; w++){
            c = inFile.get();
            switch(c){
                case ' ':
                    walls[h][w] = false;
                    break;
                case '#':
                    walls[h][w] = true;
                    break;
                case 'B':
                    if(gotBase)
                        throw runtime_error("Multiple bases in map");
                    gotBase = true;
                    base.m_Y = (int)h;
                    base.m_X = (int)w;

                    walls[h][w] = false;
                    break;
                case 'S':
                    spawns.emplace_back(w, h);
                    walls[h][w] = false;
                    break;
                default:
                    throw runtime_error("Incorrect map file format");
            }
        }
        if(inFile.get() != '\n')
            throw runtime_error("Incorrect map file format");
    }
    if(spawns.empty())
        throw runtime_error("No troop spawns in chosen map file");
    m_Width = width;
    m_Height = height;
    m_Spawns = spawns;
    m_Walls = walls;
    m_Base = base;
    m_BaseHealth = health;
    m_Waves = waves;
    for(size_t h = 0; h < walls.size(); h++){
        for(size_t w = 0; w < walls[h].size(); w++){
            m_Heatmap[CCoord((int)w, (int)h)] = 0;
        }
    }
    deque<CCoord> path;
    for(const auto& coord : m_Spawns){
        path = FindGroundPath(coord);
        while(!path.empty()){
            m_Heatmap[path.front()] += 1;
            path.pop_front();
        }
        path = FindAirPath(coord);
        while(!path.empty()){
            m_Heatmap[path.front()] += 1;
            path.pop_front();
        }
    }
}

std::vector<std::vector<char>> CMap::DrawMap() const {
    vector<vector<char>> buffer(m_Height, vector<char>(m_Width + 1, ' '));
    for(size_t h = 0; h < m_Height; h++){
        for(size_t w = 0; w < m_Width; w++){
            if(m_Walls[h][w])
                buffer[h][w] = '#';
        }
        buffer[h][m_Width] = '\n';
    }
    for(auto s : m_Spawns){
        buffer[s.m_Y][s.m_X] = 'S';
    }
    buffer[m_Base.m_Y][m_Base.m_X] = 'B';
    return buffer;
}

void CMap::PrintHeatmap(){
    vector<vector<char>> buffer(m_Height, vector<char>(m_Width + 1, ' '));
    for(auto a : m_Heatmap)
        buffer[a.first.m_Y][a.first.m_X] = a.second + '0';
    for(size_t h = 0; h < m_Height; h++) {
        buffer[h][m_Width] = '\n';
        for(auto c : buffer[h])
            cout << c;
    }
    cout << endl;
}

std::vector<std::vector<bool>> CMap::GetWalls() const {
    return m_Walls;
}

CCoord CMap::GetBase() const {
    return m_Base;
}

std::map<CCoord, std::vector<CCoord>> CMap::MakeGraph() const {
    map<CCoord, vector<CCoord>> graph;
    for(size_t h = 1; h < m_Walls.size(); h++){
        for(size_t w = 1; w < m_Walls[h].size(); w++){
            if(m_Walls[h][w])
                continue;
            vector<CCoord> node;
            if(!m_Walls[h - 1][w])
                node.emplace_back(w, h - 1);
            if(!m_Walls[h + 1][w])
                node.emplace_back(w, h + 1);
            if(!m_Walls[h][w - 1])
                node.emplace_back(w - 1, h);
            if(!m_Walls[h][w + 1])
                node.emplace_back(w + 1, h);
            graph[CCoord((int)w, (int)h)] = node;
        }
    }
    return graph;
}

CMap &CMap::AttackBase() {
    if(m_BaseHealth != 0)
        m_BaseHealth--;
    return *this;
}

size_t CMap::GetBaseHealth() const {
    return m_BaseHealth;
}

CMap::CMap() : m_Height(0), m_Width(0), m_Walls{}, m_Base(), m_Spawns{}, m_BaseHealth(0) {}

std::vector<CCoord> CMap::GetSpawns() const {
    return m_Spawns;
}

std::deque<CCoord> CMap::FindAirPath(CCoord spawn) const {
    CCoord base = m_Base;
    deque<CCoord> path;
    CCoord cur = spawn;
    while(cur != base){
        if(abs((int)(cur.m_X - base.m_X)) > abs((int)(cur.m_Y - base.m_Y)))
            cur.m_X > base.m_X ? cur.m_X -= 1 : cur.m_X += 1;
        else
            cur.m_Y > base.m_Y ? cur.m_Y -= 1 : cur.m_Y += 1;
        path.push_back(cur);
    }
    return path;
}

std::deque<CCoord> CMap::FindGroundPath(CCoord spawn) const {
    CCoord base = m_Base;
    map<CCoord, vector<CCoord>> graph = MakeGraph();
    set<CCoord> visited;
    deque<CCoord> queue;
    visited.insert(spawn);
    queue.push_back(spawn);
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
    path.pop_front();
    return path;
}

std::map<CCoord, int> CMap::GetHeatmap() const {
    return m_Heatmap;
}

size_t CMap::GetWaves() const {
    return m_Waves;
}

