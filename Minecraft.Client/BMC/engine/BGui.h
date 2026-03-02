#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#ifdef _WINDOWS64
#include <Windows.h>
#include <d3d11.h>
#include "../libs/imgui/imgui.h"
#include "../libs/imgui/imgui_impl_win32.h"
#include "../libs/imgui/imgui_impl_dx11.h"
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#define IMGUI_INIT_WINDOW(...) ImGui_ImplWin32_WndProcHandler(__VA_ARGS__)
#endif

#define ROUTE(path, cl) { path, std::make_shared<cl>(shared_from_this()) }

class Window;

struct RenderDeviceContext {
#ifdef _WINDOWS64
    struct {
        void* device;
        void* context;
        void* renderTargetView;
        void* depthStencilView;
    } d3d11;
#endif
};

class BGui : public std::enable_shared_from_this<BGui> {
public:
    void Setup();

    void Init();
    void Destroy();

    void PushRoute(const std::string& route);
    void PopRoute();

    void SetupWindow(void* wnd);
    void SetupRenderContext(RenderDeviceContext context);

    void StartFrame();
    void EndFrame();
private:
    void* mHWND;
    RenderDeviceContext mRenderContext;

    std::unordered_map<std::string, std::shared_ptr<Window>> mRoutes;
    std::string mCurrentRoute;
};