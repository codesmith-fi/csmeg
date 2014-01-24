#include "CTesterGame.h"

#include <iostream>
#include <exception>


using namespace std;
using namespace csmeg;

int main()
{
    try {
        CTesterGame game;
        game.Run();
    } catch( exception& e ) {
        cerr << "Error: " << e.what() << endl;
    }
    return 0;
}
