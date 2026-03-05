#pragma once

#include <cstdint>
#include <string>
#include <vector>
#include <unordered_map>

class Achievement;

typedef struct AchievementSaveEntry {
    const char* id;
    int32_t progress;
} AchievementSaveEntry;

struct AchievementSaveData {
    bool cheated;
    AchievementSaveEntry entries[100];
};

typedef struct AchievementProgress {
    int32_t progress;
    bool achieved;
} AchievementProgress;

#define HAS_ACHIEVEMENTS(fileNum) (true)

#ifdef __cplusplus
#include <map>
extern AchievementProgress* Achievement_GetProgress(const std::string& id);
void Achievement_Register(Achievement* achievement);
Achievement* Achievement_FindByAward(int award);
#endif