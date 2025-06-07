#include <iostream>
#include <random>
#include <cmath>
#include <fstream>
#include <vector>
#include <algorithm>

// BST 節點
struct Node {
    int value;
    Node* left;
    Node* right;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

// BST 類
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

    // 找到右子樹最小值節點
    Node* findMin(Node* node) {
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    // 刪除節點
    Node* remove(Node* node, int k) {
        if (!node) {
            return nullptr;
        }
        if (k < node->value) {
            node->left = remove(node->left, k);
        } else if (k > node->value) {
            node->right = remove(node->right, k);
        } else {
            // 無子節點或單子節點
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }
            // 雙子節點
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
    std::ofstream out("bst_ratios.txt"); // 輸出到檔案

    for (int n : n_values) {
        double total_ratio = 0.0;
        int trials = 10; // 多次模擬取平均
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