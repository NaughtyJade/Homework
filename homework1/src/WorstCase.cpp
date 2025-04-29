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