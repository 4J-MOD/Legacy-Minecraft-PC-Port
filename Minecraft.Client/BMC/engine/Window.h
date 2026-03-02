#pragma once

#include <memory>

#include "BGui.h"
#include "IconsFrontAwesome4.h"

class Window {
public:
    Window(std::shared_ptr<BGui> gui);

    virtual void Init();
    virtual void Destroy();
    virtual void StartFrame();
    virtual void EndFrame();

private:
    std::shared_ptr<BGui> mGui;
};