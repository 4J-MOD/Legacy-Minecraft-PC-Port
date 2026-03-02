#include "SettingsWindow.h"
#include "GameRenderer.h"

void SettingsWindow::Init() {
    // Initialize settings window
}

void SettingsWindow::Destroy() {
    // Destroy settings window
}

void SettingsWindow::StartFrame() {
    Minecraft* mc = Minecraft::GetInstance();

    int music = app.GetGameSettings(eGameSetting_MusicVolume);
    int sound = app.GetGameSettings(eGameSetting_SoundFXVolume);
    float fov = mc->gameRenderer->GetFovVal();

    ImGui::Begin("Settings");

    if(UIWidgets::CVarInputString("Player Name", "gGame.playerName", UIWidgets::InputOptions{.defaultValue = "PlayerName"})) {
        
    }
    
    if(UIWidgets::CVarInputString("Display Name", "gGame.displayName", UIWidgets::InputOptions{.defaultValue = "PlayerName"})) {
        
    }

    if(UIWidgets::SliderInt("Music Volume", &music, UIWidgets::IntSliderOptions{ .min = 0, .max = 100 })) {
        app.SetGameSettings(0, eGameSetting_MusicVolume, music);	
    }
    
    if(UIWidgets::SliderInt("Sound Volume", &sound, UIWidgets::IntSliderOptions{ .min = 0, .max = 100 })) {
        app.SetGameSettings(0, eGameSetting_SoundFXVolume, sound);	
    }

    if(UIWidgets::SliderFloat("FOV", &fov, UIWidgets::FloatSliderOptions{ .min = 0.0f, .max = 100.0f })) {
        mc->gameRenderer->SetFovVal(fov);
    }


    ImGui::End();
}

void SettingsWindow::EndFrame() {
    // End frame for settings window
}