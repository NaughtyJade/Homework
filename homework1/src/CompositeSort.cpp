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