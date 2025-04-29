#ifndef TEST_CASE_GENERATOR_H
#define TEST_CASE_GENERATOR_H

#include <vector>

// 產生 Insertion Sort 的最壞情況（遞減序列）
std::vector<int> generateWorstCaseInsertion(int n);

// 產生 Quick Sort 的最壞情況（已排序序列，近乎有序）
std::vector<int> generateWorstCaseQuick(int n);

#endif
