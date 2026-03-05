#pragma once

#include "../BMC.h"

class SettingsWindow : public Window {
public:
    SettingsWindow(std::shared_ptr<BGui> gui) : Window(gui) {}

    void Init() override;
    void Destroy() override;
    void StartFrame() override;
    void EndFrame() override;
};