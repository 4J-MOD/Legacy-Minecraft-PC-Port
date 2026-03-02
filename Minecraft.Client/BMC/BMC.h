#pragma once

#include <unordered_map>
#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <locale>
#include <codecvt>

#include "engine/BGui.h"
#include "engine/Types.h"
#include "engine/Window.h"
#include "engine/Config.h"
#include "engine/UIWidgets.h"
#include "engine/ShipInit.hpp"
#include "engine/ConsoleVariable.h"
#include "bridge/cvar.h"
#include "system/achievements/AchievementImpl.h"

// Minecraft Stuff
#include "stdafx.h"
#include "../Minecraft.World/Achievement.h"

class BMC {
public:
    static BMC& GetInstance();

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

    BMC();
    ~BMC() = default;
protected:
    std::shared_ptr<BGui> mGui;
    std::shared_ptr<Ship::Config> mConfig;
    std::shared_ptr<Ship::ConsoleVariable> mConsoleVariables;
};

namespace BMCUtil {
inline std::string narrow(const std::wstring& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> myconv;
    return myconv.to_bytes(str);
}
}