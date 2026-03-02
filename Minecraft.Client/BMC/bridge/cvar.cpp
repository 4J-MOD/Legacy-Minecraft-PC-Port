#include "cvar.h"

#include "../BMC.h"

std::shared_ptr<Ship::CVar> CVarGet(const char* name) {
    return BMC::GetInstance().GetConsoleVariables()->Get(name);
}

extern "C" {
int32_t CVarGetInteger(const char* name, int32_t defaultValue) {
    return BMC::GetInstance().GetConsoleVariables()->GetInteger(name, defaultValue);
}

float CVarGetFloat(const char* name, float defaultValue) {
    return BMC::GetInstance().GetConsoleVariables()->GetFloat(name, defaultValue);
}

const char* CVarGetString(const char* name, const char* defaultValue) {
    return BMC::GetInstance().GetConsoleVariables()->GetString(name, defaultValue);
}

Color_RGBA8 CVarGetColor(const char* name, Color_RGBA8 defaultValue) {
    return BMC::GetInstance().GetConsoleVariables()->GetColor(name, defaultValue);
}

Color_RGB8 CVarGetColor24(const char* name, Color_RGB8 defaultValue) {
    return BMC::GetInstance().GetConsoleVariables()->GetColor24(name, defaultValue);
}

void CVarSetInteger(const char* name, int32_t value) {
    BMC::GetInstance().GetConsoleVariables()->SetInteger(name, value);
}

void CVarSetFloat(const char* name, float value) {
    BMC::GetInstance().GetConsoleVariables()->SetFloat(name, value);
}

void CVarSetString(const char* name, const char* value) {
    BMC::GetInstance().GetConsoleVariables()->SetString(name, value);
}

void CVarSetColor(const char* name, Color_RGBA8 value) {
    BMC::GetInstance().GetConsoleVariables()->SetColor(name, value);
}

void CVarSetColor24(const char* name, Color_RGB8 value) {
    BMC::GetInstance().GetConsoleVariables()->SetColor24(name, value);
}

void CVarRegisterInteger(const char* name, int32_t defaultValue) {
    BMC::GetInstance().GetConsoleVariables()->RegisterInteger(name, defaultValue);
}

void CVarRegisterFloat(const char* name, float defaultValue) {
    BMC::GetInstance().GetConsoleVariables()->RegisterFloat(name, defaultValue);
}

void CVarRegisterString(const char* name, const char* defaultValue) {
    BMC::GetInstance().GetConsoleVariables()->RegisterString(name, defaultValue);
}

void CVarRegisterColor(const char* name, Color_RGBA8 defaultValue) {
    BMC::GetInstance().GetConsoleVariables()->RegisterColor(name, defaultValue);
}

void CVarRegisterColor24(const char* name, Color_RGB8 defaultValue) {
    BMC::GetInstance().GetConsoleVariables()->RegisterColor24(name, defaultValue);
}

void CVarClear(const char* name) {
    BMC::GetInstance().GetConsoleVariables()->ClearVariable(name);
}

void CVarClearBlock(const char* name) {
    BMC::GetInstance().GetConsoleVariables()->ClearBlock(name);
}

void CVarCopy(const char* from, const char* to) {
    BMC::GetInstance().GetConsoleVariables()->CopyVariable(from, to);
}

void CVarLoad() {
    BMC::GetInstance().GetConsoleVariables()->Load();
}

void CVarSave() {
    BMC::GetInstance().GetConsoleVariables()->Save();
}
}
