/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#pragma once


#include <iostream>
#include "CMap.h"
#include "CTroopStore.h"

class CInterface {
private:
    std::istream & m_In;
    std::ostream & m_Out;
public:
    CInterface(std::istream& in, std::ostream& out);
    std::string PromptFilename(const std::string& type);
    size_t PromptNumber();
    CInterface& ClearInput();

    CInterface& FlushBuffer(const std::vector<std::vector<char>>& buffer);
    CInterface& FlushBuffer(const std::vector<std::vector<char>>& buffer, size_t health);
    CInterface& PrintTroopStore(const std::vector<std::unique_ptr<CTroop>>& store, size_t coins, size_t wave, size_t waves);
    CInterface& PrintLine(const std::string& line);
    CInterface& PrintResult(bool won, size_t score);
    CCoord ChooseSpawn(std::vector<CCoord> spawns, const std::string& type);
    CInterface& PrintHealth(size_t health);

    void Continue();

};
