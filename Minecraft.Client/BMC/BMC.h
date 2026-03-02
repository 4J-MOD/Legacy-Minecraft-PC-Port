#pragma once

#include <cstdint>
#include <memory>

#include "engine/BGui.h"
#include "engine/Types.h"
#include "engine/Window.h"
#include "engine/Config.h"
#include "engine/UIWidgets.h"
#include "engine/ShipInit.hpp"
#include "engine/ConsoleVariable.h"

class BMC {
public:
    static BMC& GetInstance() {
        static BMC instance;
        return instance;
    }

    std::shared_ptr<Ship::Config> GetConfig() {
        return mConfig;
    }

    std::shared_ptr<Ship::ConsoleVariable> GetConsoleVariables() {
        return mConsoleVariables;
    }

    std::shared_ptr<BGui> GetGui() {
        return mGui;
    }

    void SaveConfig() {
        mConfig->Save();
    }
protected:
    BMC();
    ~BMC() = default;
    std::shared_ptr<BGui> mGui;
    std::shared_ptr<Ship::Config> mConfig;
    std::shared_ptr<Ship::ConsoleVariable> mConsoleVariables;
};