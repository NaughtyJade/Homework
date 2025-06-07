#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

double calculateInputTime(int k, int n, int m, int S, double ts, double tl, double tt) {
    double run_size = static_cast<double>(n) / m;
    double buffer_size = static_cast<double>(S) / k;
    double reads_per_run = std::ceil(run_size / buffer_size);
    double total_reads = k * reads_per_run;
    double time_per_access = ts + tl + buffer_size * tt;
    return total_reads * time_per_access;
}

int main() {
    int n = 200000, m = 64, S = 2000;
    double ts = 0.08, tl = 0.02, tt = 0.001;
    std::vector<int> k_values = {2, 5, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    std::ofstream out("input_times.txt"); // 輸出到檔案

    for (int k : k_values) {
        double t_input = calculateInputTime(k, n, m, S, ts, tl, tt);
        out << k << " " << t_input << "\n";
    }
    out.close();
    return 0;
}