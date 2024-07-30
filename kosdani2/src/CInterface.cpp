/**
 * @author Daniel Kos <kosdani2@fit.cvut.cz>
 * @date 07.06.2023
 */

#include "CInterface.h"
#include "constants.h"


using namespace std;

CInterface::CInterface ( istream & in, ostream & out )
        : m_In( in ), m_Out( out ) {
    m_In.exceptions( ios::badbit | ios::eofbit );
    m_Out.exceptions( ios::failbit | ios::badbit | ios::eofbit );
}

CInterface & CInterface::ClearInput (){
    m_In.clear();
    m_In.ignore( std::numeric_limits<std::streamsize>::max(), '\n' );
    return *this;
}

std::string CInterface::PromptFilename(const string& type) {
    //ClearInput();
    m_Out << "Enter filename with " << type << " or enter to use default:" << endl;
    string file;
    if(!getline(m_In, file))
        throw runtime_error("Error while getting filename");
    return file;
}


CInterface &CInterface::FlushBuffer(const vector<vector<char>>& buffer) {
    system("clear");
    for(size_t h = 0; h < buffer.size(); h++){
        for(char c : buffer[h])
            m_Out << c;
    }
    m_Out << flush;
    return *this;
}



CInterface &CInterface::PrintTroopStore(const std::vector<std::unique_ptr<CTroop>>& store, size_t coins, size_t wave, size_t waves) {
    m_Out << "You have " << coins << " coins left.\n";
    for(size_t idx = 0; idx < store.size(); idx++){
        m_Out << idx << " : " << *store[idx] << "\n";
    }
    m_Out << store.size() << " : Exit store and launch the attack ";
    wave < waves ? m_Out << "(wave #" << wave << ")" << endl : m_Out << "(last wave!)" << endl;
    return *this;
}

size_t CInterface::PromptNumber() {
    //ClearInput();
    size_t nr;
    m_Out << "Enter number:" << endl;
    while(!(m_In >> nr)) {
        m_Out << "Please enter a valid number:" << endl;
        ClearInput();

    }
    m_In.get();
    return nr;
}

CInterface &CInterface::PrintLine(const string &line) {
    m_Out << line << endl;
    return *this;
}

CInterface &CInterface::PrintResult(bool won, size_t score) {
    won? m_Out << "Congratulations, you won! " : m_Out << "You lost. ";
    m_Out << "Final score: " << score << endl;
    return *this;
}

CCoord CInterface::ChooseSpawn(std::vector<CCoord> spawns, const std::string& type) {
    if(spawns.size() == 1)
        return spawns[0];
    m_Out << "Choose spawn for " << type << ". Available spawns:\n";
    for(size_t idx = 0; idx < spawns.size(); idx++){
        m_Out << idx << " : (" << spawns[idx].m_X << "," << spawns[idx].m_Y << ")   ";
    }
    size_t chosen = PromptNumber();
    while(chosen >= spawns.size()){
        m_Out << "Invalid spawn number.\n";
        chosen = PromptNumber();
    }
    return spawns[chosen];
}

void CInterface::Continue() {
    m_Out << "enter to continue" << endl;
    while(m_In.get() != '\n'){}
}

CInterface &CInterface::PrintHealth(size_t health) {
    m_Out << "Base has " << health << " health left" << endl;
    return *this;
}

CInterface &CInterface::FlushBuffer(const vector<std::vector<char>> &buffer, size_t health) {
    FlushBuffer(buffer);
    PrintHealth(health);
    return *this;
}







