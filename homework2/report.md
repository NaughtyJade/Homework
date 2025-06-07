# 4104322841043234

作業二

## 解題說明

![image](https://github.com/user-attachments/assets/679033c8-5696-43d5-872c-fe7d98dfd00d)

![image](https://github.com/user-attachments/assets/6e4c61e0-1d79-43a2-85f5-07d1569aceeb)

![image](https://github.com/user-attachments/assets/7c19fc6d-e9f3-4e15-ba81-1ced022bede4)

 利用Grok和網路上的資料並使用C++ 實現核心演算法，Python + Matplotlib 繪製圖表，並分析每個操作的時間與空間複雜度。 
 - Min Heap
 - Binary Search Tree
 - 課本第457頁的練習1

 
## 程式實作

Min Heap 實作：

```cpp
#include <vector>
#include <stdexcept>

// MinPQ ?質情憿?
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

// MinHeap 撖衣
template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

    // 銝蕪嚗?蝝Ｗ? i ??蝝?銝矽??
    void SiftUp(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (heap[i] < heap[parent]) {
                std::swap(heap[i], heap[parent]);
                i = parent;
            } else {
                break;
            }
        }
    }

    // 銝蕪嚗?蝝Ｗ? i ??蝝?銝矽??
    void SiftDown(int i) {
        int n = heap.size();
        while (true) {
            int smallest = i;
            int left = 2 * i + 1;
            int right = 2 * i + 2;
            if (left < n && heap[left] < heap[smallest]) {
                smallest = left;
            }
            if (right < n && heap[right] < heap[smallest]) {
                smallest = right;
            }
            if (smallest == i) {
                break;
            }
            std::swap(heap[i], heap[smallest]);
            i = smallest;
        }
    }

public:
    bool IsEmpty() const override {
        return heap.empty();
    }

    const T& Top() const override {
        if (IsEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        return heap[0];
    }

    void Push(const T& value) override {
        heap.push_back(value);
        SiftUp(heap.size() - 1);
    }

    void Pop() override {
        if (IsEmpty()) {
            throw std::runtime_error("Heap is empty");
        }
        heap[0] = heap.back();
        heap.pop_back();
        if (!IsEmpty()) {
            SiftDown(0);
        }
    }
};
```

Binary Search Tree 實作：

```cpp
#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

// BST 蝭暺?
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// BST 憿?
class BST {
private:
    Node* root;

    Node* insert(Node* node, int value) {
        if (!node) {
            return new Node(value);
        }
        if (value < node->value) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    int height(Node* node) const {
        if (!node) {
            return 0;
        }
        return 1 + std::max(height(node->left), height(node->right));
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    // ?曉?喳?璅寞?撠潛?暺?
    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // ?芷蝭暺?
    Node* remove(Node* node, int k) {
        if (!node) {
            return nullptr;
        }
        if (k < node->value) {
            node->left = remove(node->left, k);
        } else if (k > node->value) {
            node->right = remove(node->right, k);
        } else {
            // ?∪?蝭暺??桀?蝭暺?
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // ??蝭暺?
            Node* minNode = findMin(node->right);
            node->value = minNode->value;
            node->right = remove(node->right, minNode->value);
        }
        return node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(int value) {
        root = insert(root, value);
    }

    int getHeight() const {
        return height(root);
    }

    void remove(int k) {
        root = remove(root, k);
    }
};





int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 1000000);

    std::vector<int> n_values = {100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    std::vector<double> ratios;
    std::ofstream out("bst_ratios.txt"); // 頛詨?唳?獢?

    for (int n : n_values) {
        double total_ratio = 0.0;
        int trials = 10; // 憭活璅⊥?像??
        for (int t = 0; t < trials; ++t) {
            BST bst;
            for (int i = 0; i < n; ++i) {
                bst.insert(dis(gen));
            }
            int h = bst.getHeight();
            double log_n = std::log2(n);
            total_ratio += h / log_n;
        }
        double avg_ratio = total_ratio / trials;
        ratios.push_back(avg_ratio);
        out << n << " " << avg_ratio << "\n";
    }
    out.close();
    return 0;
}
```

課本第457頁的練習 1實作：

```cpp
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
    std::ofstream out("input_times.txt"); // 頛詨?唳?獢?

    for (int k : k_values) {
        double t_input = calculateInputTime(k, n, m, S, ts, tl, tt);
        out << k << " " << t_input << "\n";
    }
    out.close();
    return 0;
}
```

## 效能分析

### 1. 時間複雜度

- **MinHeap**
  - IsEmpty：O(1)
  - Top：O(1)
  - Push：O(log n)
  - Pop：O(log n)

- **BinerySearchTree**
  - 插入：O(n)
  - 高度計算：O(n)
  - 刪除：O(n)
  - 主程式：O(n log n)
  
- **t_input**
  - 計算：O(1)（每次 k 的計算）
  - 主程式：O(k)（遍歷 k_values）
  
### 2. 空間複雜度

- **MinHeap**
  - 主要空間：O(n)

- **BinerySearchTree**
  - 主要空間：O(n)

- **t_input**
  - 主要空間：O(1)

## 測試與驗證

```shell
$ g++ MinHeap.cpp -o MinHeap
$ ./MinHeap

$ g++ BinarySearchTree.cpp -o BinarySearchTree
$ ./BinarySearchTree

$ g++ CalTInput.cpp -o CalTInput
$ ./CalTInput
```

![BSTRatios](https://github.com/user-attachments/assets/29894331-31b3-4f3a-b9bd-2a9cdb64c1c7)

![Tinput](https://github.com/user-attachments/assets/30016da8-da95-457a-95d1-c90b1cc36dfa)

## 申論及開發報告

以模組化方式實現：
- **問題 1**：`MinHeap.cpp` 將 MinPQ 抽象類與 MinHeap 分離
- **問題 2**：`BinarySearchTree.cpp` 整合插入、高度計算和刪除功能，減少檔案數量。
- **問題 3**：`CalTInput.cpp` 實現 t_input 計算公式，`TInput.py` 繪製 k 的影響。



---
