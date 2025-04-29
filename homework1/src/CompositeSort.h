#ifndef COMPOSITE_SORT_H
#define COMPOSITE_SORT_H

#include <vector>

long long mergeAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right);

long long countInversions(std::vector<int>& arr);

void compositeSort(std::vector<int>& arr);

#endif
