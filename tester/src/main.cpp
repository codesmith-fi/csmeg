#include "CTesterGame.h"

#include <iostream>
#include <exception>

#include <csmeg/CDebug.h>

using namespace std;
using namespace csmeg;

int main()
{
    Debug::CLogger::setLogLevel(DebugLogLevel::INFO);
    LOG_INFO() << "CSMEG Tester application starting up";
    try {
        CTesterGame game;
        game.run();
    } catch( exception& e ) {
        LOG_ERROR() << "Exception, reason: " << e.what();
    }
    LOG_INFO() << "All done.";
    return 0;
}
