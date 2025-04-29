
# 4104322841043234

作業一

## 解題說明

實作排序 n 個數字的函式，包含以下：

 Insertion Sort
 
 Quick Sort 
 
 Merge Sort 
 
 Heap Sort
 
 Composite Sort
 

## 程式實作

WorstCaseData 實作：

```cpp
#include <vector>
#include <iostream>
#include "WorstCase.h"

std::vector<int> generateWorstCaseInsertion(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
    return arr;
}
std::vector<int> generateWorstCaseQuick(int n) {
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) arr[i] = i; // 近乎有序
    return arr;
}
```

AverageCaseData 實作：

```cpp

#include "permute.h"
#include <cstdlib>

void permute(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}
```

空間與時間複雜度測試 實作：

```cpp
#include "SortUtils.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>

double measureTime(std::function<void(std::vector<int>&)> sortFunc, std::vector<int> arr, int repeat) {
    double totalTime = 0;
    for (int i = 0; i < repeat; ++i) {
        std::vector<int> temp = arr;
        auto start = std::chrono::high_resolution_clock::now();
        sortFunc(temp);
        auto end = std::chrono::high_resolution_clock::now();
        totalTime += std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    }
    return totalTime / repeat;
}

size_t getMemoryUsage() {
    PROCESS_MEMORY_COUNTERS memInfo;
    GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
    return memInfo.WorkingSetSize / 1024;
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

long long countInversions(const std::vector<int>& arr) {
    long long inversions = 0;
    for (size_t i = 0; i < arr.size() - 1; ++i) {
        for (size_t j = i + 1; j < arr.size(); ++j) {
            if (arr[i] > arr[j]) ++inversions;
        }
    }
    return inversions;
}

void compositeSort(std::vector<int>& arr) {
    int n = arr.size();
    // 小規模資料：使用插入排序
    if (n < 100) {
        insertionSort(arr);
        return;
    }
    // 檢查是否近乎有序
    long long inversions = countInversions(arr);
    double inversion_ratio = static_cast<double>(inversions) / (n * (n - 1) / 2.0);
    if (inversion_ratio < 0.1) {
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

    // 輸出表頭
    std::cout << std::left << std::setw(15) << "n";
    for (const auto& name : sortNames) {
        std::cout << std::setw(25) << (name + " Worst (us)") << std::setw(25) << (name + " Avg (us)");
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
            double worstTime = measureTime(sorts[i], worstData);
            // 測量平均情況
            double avgTime = measureTime(sorts[i], avgData);

            std::cout << std::fixed << std::setprecision(2);
            std::cout << std::setw(25) << worstTime << std::setw(25) << avgTime;
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

Composite Sort (低有序度）：$O(n^2)$

Composite Sort (高重複率）：$O(n log n)$
 
2.空間複雜度
Insertion Sort：O(1)。

Quick Sort：O(log n)。

Merge Sort：O(log n)。

Heap Sort：O(1)。

Composite Sort：取決於選擇的演算法。

## 測試與驗證

| n    |  Insertion Sort worst  |  Insertion Sort Avg  |  Quick Sort worst  |  Quick Sort Avg  |  Merge Sort worst  |  Merge Sort Avg  |  Heap Sort worst  |  Heap Sort Avg  |  Composite Sort worst  |  Composite Sort Avg  |
|----------|--------------|----------|----------|--------------|----------|----------|--------------|----------|----------|--------------
| 500  |         2.00           |       246.29         |       22.02        |      40.03       |       82.82         |      108.74      |      76.32        |      82.98      |         511.45         |       789.12        |
| 1000 |         5.00           |       963.74         |       50.05        |      92.08       |       187.51        |      231.40      |      173.83       |      184.50     |         1902.36        |       3167.41       |
| 2000 |         8.51           |       3724.20        |       101.83       |      211.19      |       375.55        |      492.35      |      384.96       |      401.61     |         7674.75        |       13059.47      |
| 3000 |         13.51          |       8393.36        |       170.48       |      333.52      |       568.89        |      793.19      |      610.09       |      650.33     |         17618.60       |       28792.33      |
| 4000 |         18.62          |       14912.13       |       219.75       |      451.62      |       764.79        |      1050.06     |      796.65       |      908.77     |         31037.52       |       51498.26      |
| 5000 |         20.01          |       23687.15       |       300.64       |      593.40      |       1013.63       |      1360.08     |      1019.83      |      1134.18    |         48532.64       |       83731.30      |
## 申論及開發報告
