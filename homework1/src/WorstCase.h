#ifndef WORST_CASE_H
#define WORST_CASE_H

#include <vector>

// 生成隨機資料（average-case）
std::vector<int> generateRandomData(int n);

// 生成插入排序和複合排序最壞情況（完全逆序）
std::vector<int> generateWorstCaseInsertion(int n);

// 生成快速排序最壞情況（針對中位數選取 pivot）
std::vector<int> generateWorstCaseQuick(int n);

#endif // WORST_CASE_H