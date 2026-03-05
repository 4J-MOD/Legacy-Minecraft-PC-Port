#include "AchievementImpl.h"

#include "../../BMC.h"

std::unordered_map<std::string, AchievementProgress> gAchievementProgress;
std::unordered_map<std::string, Achievement*> gAchievementList = {};

AchievementSaveData gSaveData;

void Achievement_Register(Achievement* achievement) {
    gAchievementList[BMCUtil::narrow(achievement->name)] = achievement;
}

Achievement* Achievement_FindByID(const std::string& id) {
    if (!gAchievementList.contains(id)) {
        /*SPDLOG_ERROR("Trying to find non-existent achievement with id {}", id);*/
        return nullptr;
    }

    return gAchievementList[id];
}

Achievement* Achievement_FindByAward(int award) {
    for (const auto& [id, achievement] : gAchievementList) {
        if (achievement->getAchievementID() == award) {
            return achievement;
        }
    }

    return nullptr;
}

void Achievement_Progress(const std::string& id, const int32_t amount = 1) {
    const Achievement* achievement = Achievement_FindByID(id);
    if (achievement) {
        auto& [progress, achieved] = gAchievementProgress[id];

        if (!achieved) {
            progress += amount;
            if (progress >= achievement->maxProgress) {
                achieved = true;
            } else {
                // SPDLOG_INFO("Progressed achievement {}: {}/{}", achievement->name, progress, achievement->maxProgress);
            }

            // Save after each achievement progress update to prevent loss of progress on crash
        } else {
            // SPDLOG_WARN("Trying to progress achievement {} that is already achieved", achievement->name);
        }
    } else {
        // SPDLOG_ERROR("Trying to progress non-existent achievement with id {}", id);
    }
}

AchievementProgress* Achievement_GetProgress(const std::string& id) {
    return &gAchievementProgress[id];
}

void Achievements_Load() {
    AchievementSaveData* saveData = &gSaveData;

    if (!HAS_ACHIEVEMENTS(selectedFile)) {
        size_t idx = 0;
        memset(saveData, 0, sizeof(AchievementSaveData));

        for (const auto& [id, achievement] : gAchievementList) {
            saveData->entries[idx++].id = id.c_str();
        }

        // TODO: Save
    } else {
        for (size_t i = 0; i < gAchievementList.size(); i++) {
            auto& [id, progress] = saveData->entries[i];

            gAchievementProgress[id].progress = progress;
            gAchievementProgress[id].achieved = progress >= gAchievementList[id]->maxProgress;
        }
    }
}

void Achievements_Save() {
    if (!HAS_ACHIEVEMENTS(selectedFile)) {
        return;
    }

    AchievementSaveData* saveData = &gSaveData;

    saveData->cheated = false; // TODO: Implement cheat detection

    size_t index = 0;
    for (const auto& [id, progress] : gAchievementProgress) {
        saveData->entries[index].id = id.c_str();
        saveData->entries[index].progress = progress.progress;
        index++;
    }
}

void Achievements_Init() {
    for (auto& [id, achievement] : gAchievementList) {
        gAchievementProgress[id] = { 0, false };
    }
}

static RegisterShipInitFunc initFunc(Achievements_Init);