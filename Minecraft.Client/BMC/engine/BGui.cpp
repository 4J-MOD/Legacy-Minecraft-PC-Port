#include "BGui.h"
#include "./Window.h"

void BGui::Setup() {
    mRoutes = {
        ROUTE("/", Window)
    };
    mCurrentRoute = "/";
}

// --- IGNORE ---

void BGui::Init() {
    mRoutes[mCurrentRoute]->Init();
}

void BGui::PushRoute(const std::string& route) {
    if(mRoutes.find(route) == mRoutes.end()) {
        return;
    }

    mCurrentRoute = route;
    mRoutes[mCurrentRoute]->Init();
}

void BGui::PopRoute() {
    if(mCurrentRoute.empty()) {
        return;
    }

    mRoutes[mCurrentRoute]->Destroy();
    mCurrentRoute = "";
}

void BGui::SetupWindow(void* wnd) {
#ifdef _WINDOWS64
    ImGui_ImplWin32_EnableDpiAwareness();
    float main_scale = ImGui_ImplWin32_GetDpiScaleForMonitor(::MonitorFromPoint(POINT{ 0, 0 }, MONITOR_DEFAULTTOPRIMARY));
#endif

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(main_scale);
    style.FontScaleDpi = main_scale;

#ifdef _WINDOWS64
    ImGui_ImplWin32_Init(wnd);
#endif

    mHWND = wnd;
}

void BGui::SetupRenderContext(RenderDeviceContext context) {
    mRenderContext = context;
#ifdef _WINDOWS64
    ImGui_ImplDX11_Init((ID3D11Device*) context.d3d11.device, (ID3D11DeviceContext*) context.d3d11.context);
#endif
}

void BGui::StartFrame() {
#ifdef _WINDOWS64
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
#endif
    ImGui::NewFrame();
    if(!mCurrentRoute.empty()) {
        mRoutes[mCurrentRoute]->StartFrame();
    }
}

void BGui::EndFrame() {
    if(!mCurrentRoute.empty()) {
        mRoutes[mCurrentRoute]->EndFrame();
    }

#ifdef _WINDOWS64
    ID3D11DeviceContext* ctx = (ID3D11DeviceContext*) mRenderContext.d3d11.context;
    ID3D11RenderTargetView* rtv = (ID3D11RenderTargetView*) mRenderContext.d3d11.renderTargetView;
    ID3D11DepthStencilView* dsv = (ID3D11DepthStencilView*) mRenderContext.d3d11.depthStencilView;
    ImGui::Render();
    ctx->OMSetRenderTargets(1, &rtv, nullptr);
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    ctx->OMSetRenderTargets(1, &rtv, dsv);
#endif
}

void BGui::Destroy() {
    if(!mCurrentRoute.empty()) {
        mRoutes[mCurrentRoute]->Destroy();
    }

#ifdef _WINDOWS64
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
#endif
}