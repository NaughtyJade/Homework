#include "SortUtils.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>
#include <vector>
#include <numeric>

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize / 1024; // 以 KB 為單位
}

std::pair<double, size_t> measureTimeAndMemory(std::function<void(std::vector<int>&)> sortFunc, std::vector<int> arr, int repeat) {
    double totalTime = 0;
    std::vector<size_t> memoryUsages;

    // 測量初始記憶體使用量
    size_t baseMemory = getMemoryUsage();

    // 重複執行以獲得穩定結果
    for (int i = 0; i < repeat; ++i) {
        std::vector<int> temp = arr; // 每次使用新副本
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(temp);
        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // 測量排序後的記憶體使用量，計算差值
        size_t currentMemory = getMemoryUsage();
        size_t memoryUsed = (currentMemory > baseMemory) ? currentMemory - baseMemory : 0;
        memoryUsages.push_back(memoryUsed);
    }

    // 計算平均執行時間
    double avgTime = totalTime / repeat;

    // 計算平均記憶體使用量
    size_t avgMemoryUsage = 0;
    if (!memoryUsages.empty()) {
        avgMemoryUsage = std::accumulate(memoryUsages.begin(), memoryUsages.end(), 0ULL) / memoryUsages.size();
    }

    return {avgTime, avgMemoryUsage};
}