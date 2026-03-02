#include "BMC.h"

static BMC instance;

BMC::BMC() {
    mConfig = std::make_shared<Ship::Config>("config.json");
    mConsoleVariables = std::make_shared<Ship::ConsoleVariable>();
    mGui = std::make_shared<BGui>();
    mGui->Setup();
    mGui->Init();
}

BMC& BMC::GetInstance() {
    return instance;
}