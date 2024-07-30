#include <iostream>
#include "CInterface.h"
#include "CPlayer.h"
#include "CTowerAI.h"
#include "CGame.h"

using namespace std;

int main() {
    CInterface interface(cin, cout);
    CGame game(make_unique<CPlayer>(CPlayer(interface)), make_unique<CTowerAI>(CTowerAI(interface)), interface);
    try {
        game.Initialize();
        game.Run();
    }
    catch(std::exception& e){
        cerr << e.what() << endl;
        return -1;
    }
    return 0;
}
