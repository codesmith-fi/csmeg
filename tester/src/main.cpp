#include "CTesterGame.h"

#include <iostream>
#include <CSmegException.h>

#include <CDebug.h>

using namespace std;
using namespace csmeg;

int main()
{
    Debug::CLogger::setLogLevel(DebugLogLevel::INFO);
    LOG_INFO() << "CSMEG Tester application starting up";
    try {
        CTesterGame game;
        game.run();
    } catch(CSmegException& e) {
        LOG_ERROR() << "CSMEG Exception, reason: " << e.what();
    } catch(exception& e) {
        LOG_ERROR() << "Unhandled general Exception, reason: " << e.what();
    }
    LOG_INFO() << "All done.";
    return 0;
}
