#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "CompositeSort.h"
#include "SortUtils.h"
#include "WorstCase.h"
#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>
#include <ctime>

int main() {
    srand(42); // 固定隨機種子，減少隨機排列的波動
    // 測試資料規模
    std::vector<int> ns = {500, 1000, 2000, 3000, 4000, 5000};
    // 排序演算法列表
    std::vector<std::function<void(std::vector<int>&)>> sorts = {
        insertionSort, quickSort, mergeSort, heapSort, compositeSort
    };
    // 排序演算法名稱
    std::vector<std::string> sortNames = {
        "Insertion Sort", "Quick Sort", "Merge Sort", "Heap Sort", "Composite Sort"
    };

    // 輸出表頭（執行時間與記憶體使用量）
    std::cout << std::left << std::setw(15) << "n";
    for (const auto& name : sortNames) {
        std::cout << std::setw(25) << (name + " Worst Time (us)")
                  << std::setw(25) << (name + " Avg Time (us)")
                  << std::setw(25) << (name + " Worst Mem (KB)")
                  << std::setw(25) << (name + " Avg Mem (KB)");
    }
    std::cout << std::endl;

    // 對每個資料規模進行測試
    for (int n : ns) {
        std::cout << std::setw(15) << n;
        // 生成 average-case 資料
        std::vector<int> avgData = generateRandomData(n);

        // 測試每個排序演算法
        for (size_t i = 0; i < sorts.size(); ++i) {
            // 根據演算法選擇 worst-case 資料
            std::vector<int> worstData;
            if (sortNames[i] == "Insertion Sort" || sortNames[i] == "Composite Sort") {
                worstData = generateWorstCaseInsertion(n); // 插入排序和複合排序使用完全逆序
            } else if (sortNames[i] == "Quick Sort") {
                worstData = generateWorstCaseQuick(n); // 快速排序使用針對中位數選取 pivot 的最壞情況
            } else {
                worstData = generateRandomData(n); // 合併排序和堆排序使用隨機排列
            }

            // 測量最壞情況
            auto worstResult = measureTimeAndMemory(sorts[i], worstData, 5000); // 增加重複次數
            double worstTime = worstResult.first;
            size_t worstMemory = worstResult.second;

            // 測量平均情況
            auto avgResult = measureTimeAndMemory(sorts[i], avgData, 5000); // 增加重複次數
            double avgTime = avgResult.first;
            size_t avgMemory = avgResult.second;

            // 輸出結果
            std::cout << std::fixed << std::setprecision(2);
            std::cout << std::setw(25) << worstTime
                      << std::setw(25) << avgTime
                      << std::setw(25) << worstMemory
                      << std::setw(25) << avgMemory;
        }
        std::cout << std::endl;
    }

    return 0;
}