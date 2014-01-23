#include <iostream>

#include "CTesterGame.h"


using namespace std;
using namespace csmeg;

int main()
{
    CTesterGame game;
    game.SetFPS(20);
    game.Run();

    return 0;
}
