#pragma once

#include <memory>

#include "BGui.h"
#include "IconsFrontAwesome4.h"

class Window {
public:
    Window(std::shared_ptr<BGui> gui) {
        mGui = gui;
    }

    virtual void Init() = 0;
    virtual void Destroy() = 0;
    virtual void StartFrame() = 0;
    virtual void EndFrame() = 0;

private:
    std::shared_ptr<BGui> mGui;
};