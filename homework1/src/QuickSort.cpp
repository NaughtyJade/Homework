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