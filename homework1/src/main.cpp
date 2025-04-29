#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "HeapSort.h"
#include "CompositeSort.h"
#include "SortUtils.h"
#include "permute.h"
#include <iostream>
#include <vector>
#include <functional>
#include <iomanip>
#include <ctime>

// 生成隨機資料（average-case）
std::vector<int> generateRandomData(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    permute(arr);
    return arr;
}

// 生成插入排序最壞情況（逆序）
std::vector<int> generateWorstCaseInsertion(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return arr;
}

// 生成快速排序最壞情況（近乎有序）
std::vector<int> generateWorstCaseQuick(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    return arr;
}

int main() {
    srand(time(0));
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
        // 生成測試資料
        std::vector<int> worstData = generateWorstCaseQuick(n); // 使用快速排序最壞情況
        std::vector<int> avgData = generateRandomData(n);

        // 測試每個排序演算法
        for (size_t i = 0; i < sorts.size(); ++i) {
            // 測量最壞情況
            auto worstResult = measureTimeAndMemory(sorts[i], worstData);
            double worstTime = worstResult.first;
            size_t worstMemory = worstResult.second;

            // 測量平均情況
            auto avgResult = measureTimeAndMemory(sorts[i], avgData);
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