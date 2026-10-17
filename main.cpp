#include <jni.h>
#include <android/log.h>
#include <pthread.h>
#include <unistd.h>
#include <dlfcn.h>
#include <vector>
#include <string>
#include <cmath>

#define LOG_TAG "ESP_MOD"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#define RVA_WORLD_TO_SCREEN   0x5023AB8 
#define RVA_PAWN_GET_NAME     0x51B8BDC 
#define RVA_PAWN_GET_TEAM     0x51B89CC 
#define RVA_PAWN_GET_ALIVE    0x51B7C40 

uintptr_t base_addr = 0;
bool espEnabled = true;

void* (*WorldToScreen)(void* camera, void* vec3) = nullptr;
void* (*GetPlayerName)(void* pawn) = nullptr;
int   (*GetTeamId)(void* pawn) = nullptr;
bool  (*GetIsAlive)(void* pawn) = nullptr;

__attribute__((constructor))
void on_load() {
    LOGI("ESP Mod Menu Loaded!");
    void* handle = dlopen("libil2cpp.so", RTLD_LAZY);
    if (!handle) {
        LOGI("Error: Cannot find libil2cpp.so");
        return;
    }
    base_addr = (uintptr_t)handle; 
    WorldToScreen = (void* (*)(void*, void*))(base_addr + RVA_WORLD_TO_SCREEN);
    GetPlayerName = (void* (*)(void*))(base_addr + RVA_PAWN_GET_NAME);
    GetTeamId = (int (*)(void*))(base_addr + RVA_PAWN_GET_TEAM);
    GetIsAlive = (bool (*)(void*))(base_addr + RVA_PAWN_GET_ALIVE);
    LOGI("ESP Offsets Resolved Successfully!");
}
