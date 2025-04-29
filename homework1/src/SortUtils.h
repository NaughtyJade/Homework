#ifndef SORT_UTILS_H
#define SORT_UTILS_H

#include <vector>
#include <functional>
#include <utility>

// 測量執行時間（微秒）和記憶體使用量（KB），返回一對值 (time, memory)
// repeat 為重複次數，預設為 1000
std::pair<double, size_t> measureTimeAndMemory(std::function<void(std::vector<int>&)> sortFunc, std::vector<int> arr, int repeat = 1000);

// 測量當前記憶體使用量（KB）
size_t getMemoryUsage();

#endif // SORT_UTILS_H