#include <vector>
#include <stdexcept>

// MinPQ 抽象類
template <class T>
class MinPQ {
public:
    virtual ~MinPQ() {}
    virtual bool IsEmpty() const = 0;
    virtual const T& Top() const = 0;
    virtual void Push(const T&) = 0;
    virtual void Pop() = 0;
};

// MinHeap 實現
template <class T>
class MinHeap : public MinPQ<T> {
private:
    std::vector<T> heap;

    // 上濾：將索引 i 的元素向上調整
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

    // 下濾：將索引 i 的元素向下調整
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