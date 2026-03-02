#include "BMC.h"

BMC::BMC() {
    mConfig = std::make_shared<Ship::Config>("config.json");
    mConsoleVariables = std::make_shared<Ship::ConsoleVariable>();
    mGui = std::make_shared<BGui>();
    mGui->Init();
    ShipInit::InitAll();
}