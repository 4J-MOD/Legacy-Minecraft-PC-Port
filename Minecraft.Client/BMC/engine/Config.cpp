#include "Config.h"

#include <fstream>
#include <string>
#include <filesystem>
#include <unordered_map>
#include <any>

namespace fs = std::filesystem;

std::unordered_map<std::string, std::any> gRamStorage;

namespace Ship {
Config::Config(std::string path) : mPath(std::move(path)), mIsNewInstance(false) {
    Reload();
}

Config::~Config() {
    printf("Saving config...\n");
}

std::string Config::GetString(const std::string& key, const std::string& defaultValue) {
    if(gRamStorage.contains(key)) {
        try {
            return std::any_cast<std::string>(gRamStorage[key]);
        } catch (const std::bad_any_cast&) {
            printf("Type mismatch for key '%s' in RAM storage. Expected string.\n", key.c_str());
        }
    }

    return defaultValue;
}

float Config::GetFloat(const std::string& key, float defaultValue) {
    if(gRamStorage.contains(key)) {
        try {
            return std::any_cast<float>(gRamStorage[key]);
        } catch (const std::bad_any_cast&) {
            printf("Type mismatch for key '%s' in RAM storage. Expected float.\n", key.c_str());
        }
    }

    return defaultValue;
}

bool Config::GetBool(const std::string& key, bool defaultValue) {
    if(gRamStorage.contains(key)) {
        try {
            return std::any_cast<bool>(gRamStorage[key]);
        } catch (const std::bad_any_cast&) {
            printf("Type mismatch for key '%s' in RAM storage. Expected bool.\n", key.c_str());
        }
    }

    return defaultValue;
}

int32_t Config::GetInt(const std::string& key, int32_t defaultValue) {
    if(gRamStorage.contains(key)) {
        try {
            return std::any_cast<int32_t>(gRamStorage[key]);
        } catch (const std::bad_any_cast&) {
            printf("Type mismatch for key '%s' in RAM storage. Expected int32_t.\n", key.c_str());
        }
    }

    return defaultValue;
}

uint32_t Config::GetUInt(const std::string& key, uint32_t defaultValue) {
    if(gRamStorage.contains(key)) {
        try {
            return std::any_cast<uint32_t>(gRamStorage[key]);
        } catch (const std::bad_any_cast&) {
            printf("Type mismatch for key '%s' in RAM storage. Expected uint32_t.\n", key.c_str());
        }
    }

    return defaultValue;
}

bool Config::Contains(const std::string& key) {
    return gRamStorage.contains(key);
}

void Config::SetString(const std::string& key, const std::string& value) {
    gRamStorage[key] = value;
}

void Config::SetFloat(const std::string& key, float value) {
    gRamStorage[key] = value;
}

void Config::SetBool(const std::string& key, bool value) {
    gRamStorage[key] = value;
}

void Config::SetInt(const std::string& key, int32_t value) {
    gRamStorage[key] = value;
}

void Config::SetUInt(const std::string& key, uint32_t value) {
    gRamStorage[key] = value;
}

void Config::Erase(const std::string& key) {
    gRamStorage.erase(key);
}

void Config::EraseBlock(const std::string& key) {
    for (auto it = gRamStorage.begin(); it != gRamStorage.end();) {
        if (it->first.rfind(key + ".", 0) == 0) {
            it = gRamStorage.erase(it);
        } else {
            ++it;
        }
    }
}

void Config::Copy(const std::string& fromKey, const std::string& toKey) {
    if (gRamStorage.contains(fromKey)) {
        gRamStorage[toKey] = gRamStorage[fromKey];
    }
}

void Config::Reload() {
    // TODO: Implement loading from file
}

void Config::Save() {
    // TODO: Implement saving to file
}

template <typename T> std::vector<T> Config::GetArray(const std::string& key) {
    if (nlohmann::json tmp = Nested(key); tmp.is_array()) {
        return tmp.get<std::vector<T>>();
    }
    return std::vector<T>();
};

template <typename T> void Config::SetArray(const std::string& key, std::vector<T> array) {
    mFlattenedJson[FormatNestedKey(key)] = nlohmann::json(array);
}

bool Config::RegisterVersionUpdater(std::shared_ptr<ConfigVersionUpdater> versionUpdater) {
    auto [_, emplaced] = mVersionUpdaters.emplace(versionUpdater->GetVersion(), versionUpdater);
    return emplaced;
}

void Config::RunVersionUpdates() {
    for (auto [_, versionUpdater] : mVersionUpdaters) {
        uint32_t version = GetUInt("ConfigVersion", 0);
        if (version < versionUpdater->GetVersion()) {
            versionUpdater->Update(this);
            SetUInt("ConfigVersion", versionUpdater->GetVersion());
        }
    }
    Save();
}

ConfigVersionUpdater::ConfigVersionUpdater(uint32_t toVersion) : mVersion(toVersion) {
}

uint32_t ConfigVersionUpdater::GetVersion() {
    return mVersion;
}

} // namespace Ship
