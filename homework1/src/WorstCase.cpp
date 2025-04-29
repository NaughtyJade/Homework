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