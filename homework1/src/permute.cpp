#include "permute.h"
#include <cstdlib>

void permute(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = n - 1; i >= 1; --i) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}