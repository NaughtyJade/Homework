# 4104322841043234

作業一

## 解題說明

![image](https://github.com/user-attachments/assets/9235ef96-b978-433f-bf7c-1ca84decbf91)


利用Grok和網路上的資料實作排序 n 個數字的函式，包含以下：

 Insertion Sort、Quick Sort、Merge Sort、Heap Sort、Composite Sort

 並實際測量個演算法所需的實際時間和空間
 

## 程式實作

TestData 實作：

```cpp
#include "WorstCase.h"
#include "permute.h"

// 生成隨機資料（average-case）
std::vector<int> generateRandomData(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
    permute(arr);
    return arr;
}

// 生成插入排序和複合排序最壞情況（完全逆序）
std::vector<int> generateWorstCaseInsertion(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i - 1; // 完全逆序
    return arr;
}

// 生成快速排序最壞情況（針對中位數選取 pivot）
std::vector<int> generateWorstCaseQuick(int n) {
    std::vector<int> arr(n);
    int mid = n / 2;
    for (int i = 0; i < n; ++i) {
        if (i < mid) {
            arr[i] = i * 2; // 前半部分：0, 2, 4, ...
        } else {
            arr[i] = (i - mid) * 2 + 1; // 後半部分：1, 3, 5, ...
        }
    }
    // 結果陣列形如 [0, 2, 4, ..., 1, 3, 5, ...]
    return arr;
}
```

空間與時間複雜度測試 實作：

```cpp
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
```

quicksort 實作：

```cpp
#include "QuickSort.h"
#include <algorithm>

int medianOfThree(std::vector<int>& arr, int low, int high) {
    int mid = low + (high - low) / 2;
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    if (arr[mid] > arr[high]) std::swap(arr[mid], arr[high]);
    if (arr[low] > arr[mid]) std::swap(arr[low], arr[mid]);
    return mid;
}

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIdx = medianOfThree(arr, low, high);
        std::swap(arr[pivotIdx], arr[high]);
        int pivot = arr[high];
        int i = low - 1;
        for (int j = low; j < high; ++j) {
            if (arr[j] <= pivot) {
                ++i;
                std::swap(arr[i], arr[j]);
            }
        }
        std::swap(arr[i + 1], arr[high]);
        int pi = i + 1;
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void quickSort(std::vector<int>& arr) {
    quickSort(arr, 0, arr.size() - 1);
}
```

mergesort 實作：

```cpp
#include "MergeSort.h"
#include <algorithm>

void merge(std::vector<int>& arr, int left, int mid, int right) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = 0; i < k; ++i) arr[left + i] = temp[i];
}

void mergeSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int curr_size = 1; curr_size < n; curr_size *= 2) {
        for (int left = 0; left < n - curr_size; left += 2 * curr_size) {
            int mid = left + curr_size - 1;
            int right = std::min(left + 2 * curr_size - 1, n - 1);
            merge(arr, left, mid, right);
        }
    }
}
```

heapsort 實作：

```cpp
#include "HeapSort.h"

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n / 2 - 1; i >= 0; --i) heapify(arr, n, i);
    for (int i = n - 1; i > 0; --i) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}
```

insertionsort  實作：

```cpp
#include "InsertionSort.h"

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}
```

compositesort  實作：

```cpp
#include "CompositeSort.h"
#include "InsertionSort.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include <algorithm>

// 使用合併排序計算逆序對，時間複雜度 O(n log n)
long long mergeAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    long long inversions = 0;
    int i = left, j = mid + 1, k = left;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        } else {
            temp[k++] = arr[j++];
            inversions += mid - i + 1; // 計算逆序對
        }
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    for (i = left; i <= right; ++i) arr[i] = temp[i];
    return inversions;
}

long long countInversions(std::vector<int>& arr) {
    std::vector<int> temp(arr.size());
    std::vector<int> copy = arr; // 複製一份陣列以避免修改原始資料
    long long inversions = 0;
    int n = copy.size();
    
    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = left + size - 1;
            int right = std::min(left + 2 * size - 1, n - 1);
            inversions += mergeAndCount(copy, temp, left, mid, right);
        }
    }
    return inversions;
}

void compositeSort(std::vector<int>& arr) {
    int n = arr.size();
    // 小規模資料：使用插入排序（提高閾值）
    if (n < 50) { // 從 100 降低到 50
        insertionSort(arr);
        return;
    }
    // 檢查是否近乎有序
    long long inversions = countInversions(arr);
    double inversion_ratio = static_cast<double>(inversions) / (n * (n - 1) / 2.0);
    if (inversion_ratio < 0.05) { // 從 0.1 降低到 0.05，減少進入插入排序的情況
        insertionSort(arr);
        return;
    }
    // 檢查重複元素比例
    std::vector<int> temp = arr;
    std::sort(temp.begin(), temp.end());
    int unique_count = std::unique(temp.begin(), temp.end()) - temp.begin();
    double unique_ratio = static_cast<double>(unique_count) / n;
    if (unique_ratio < 0.5) {
        mergeSort(arr);
        return;
    }
    // 預設：使用快速排序
    quickSort(arr);
}
```

主程式實作

```cpp
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
```

## 效能分析

1.時間複雜度
Insertion Sort Worst-case: $O(n^2)$

Insertion Sort Aerage-case: $O(n^2)$

Quick Sort Worst-case: $O(n^2)$

Quick Sort  Aerage-case: $O(n log n)$

Merge Sort Worst-case: $O(n log n)$

Merge Sort  Aerage-case: $O(n log n)$

Heap Sort Worst-case: $O(n log n)$

Heap Sort  Aerage-case: $O(n log n)$

Composite Sort (n < 100）：O(1)

Composite Sort (低有序度）：$O(n log n)$

Composite Sort (高重複率）：$O(n log n)$
 
2.空間複雜度
Insertion Sort：O(1)。

Quick Sort：O(log n)。

Merge Sort：O(log n)。

Heap Sort：O(1)。

Composite Sort：取決於選擇的演算法。

## 測試與驗證

```shell
$ g++ main.cpp InsertionSort.cpp QuickSort.cpp MergeSort.cpp HeapSort.cpp CompositeSort.cpp WorstCase.cpp permute.cpp SortUtils.cpp -lpsapi -o sort_test
$ ./sort_test
```

1.時間(μs)
| n    |  Insertion Sort worst  |  Insertion Sort Avg  |  Quick Sort worst  |  Quick Sort Avg  |  Merge Sort worst  |  Merge Sort Avg  |  Heap Sort worst  |  Heap Sort Avg  |  Composite Sort worst  |  Composite Sort Avg  |
|----------|--------------|----------|----------|--------------|----------|----------|--------------|----------|----------|--------------
| 500  |         569.69         |       409.32         |       502.69       |      41.88       |       118.24       |      120.30      |      96.40        |      94.65      |         117.13         |       182.32         |
| 1000 |         2541.09        |       1162.95        |       1924.20      |      104.97      |       301.54       |      347.36      |      236.30       |      213.27     |         243.87         |       435.96         |
| 2000 |         9689.96        |       5100.64        |       7657.20      |      232.35      |       560.44       |      715.64      |      475.53       |      472.07     |         681.25         |       882.79         |
| 3000 |         21733.01       |       10738.30       |       17667.50     |      426.40      |       982.30       |      956.95      |      910.35       |      886.65     |         962.86         |       1527.80        |
| 4000 |         38731.99       |       19511.23       |       31886.71     |      541.04      |       1360.43      |      1344.78     |      1175.30      |      1083.76    |         1319.05        |       2043.87        |
| 5000 |         59558.36       |       29759.68       |       48489.81     |      751.75      |       1671.40      |      1673.04     |      1332.40      |      1508.84    |         1710.93        |       2709.63        |

2.空間(KB)
| n    |  Insertion Sort worst  |  Insertion Sort Avg  |  Quick Sort worst  |  Quick Sort Avg  |  Merge Sort worst  |  Merge Sort Avg  |  Heap Sort worst  |  Heap Sort Avg  |  Composite Sort worst  |  Composite Sort Avg  |
|----------|--------------|----------|----------|--------------|----------|----------|--------------|----------|----------|--------------
| 500  |         53             |       0              |       6            |      16          |       17           |      22          |      22           |      22         |         22             |       22             |
| 1000 |         61             |       22             |       0            |      22          |       42           |      16          |      16           |      16         |         16             |       16             |
| 2000 |         81             |       12             |       40           |      19          |       60           |      15          |      15           |      15         |         23             |       15             |
| 3000 |         79             |       31             |       31           |      0           |       41           |      12          |      12           |      12         |         12             |       12             |
| 4000 |         119            |       0              |       44           |      0           |       89           |      0           |      0            |      0          |         0              |       0              |
| 5000 |         28             |       28             |       60           |      28          |       49           |      35          |      19           |      19         |         57             |       57             |

![execution_time](https://github.com/user-attachments/assets/a8228c60-5547-48d9-892e-245f7c993e18)
![memory_usage](https://github.com/user-attachments/assets/e2dd509a-787a-4412-a366-4e04776a7a19)

## 申論及開發報告
以模組化的方式把每一個sorting的實作分開寫，加上測試資料的產生用main把所有的模組包起來。

一開始用repeat100來測試時間和空間的數值，但看到很多0所以我就用repeat1000下去測才必較好。

CompositeSort的設計是以
- 資料規模
- 有序程度
- 元素重複程度
來判定，預設是用QuickSort來做。
