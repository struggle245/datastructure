#include <iostream>
#include <queue>
#include <vector>
#include <functional>

class MedianFinder {
private:
    // 最大堆：存储较小的一半数据
    std::priority_queue<int> maxHeap;
    // 最小堆：存储较大的一半数据
    std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
    
public:
    MedianFinder() {}
    
    void addNum(int num) {
        // 始终保持 maxHeap.size() >= minHeap.size()
        if (maxHeap.empty() || num <= maxHeap.top()) {
            maxHeap.push(num);
        } else {
            minHeap.push(num);
        }
        
        // 平衡两个堆的大小
        if (maxHeap.size() > minHeap.size() + 1) {
            minHeap.push(maxHeap.top());
            maxHeap.pop();
        } else if (minHeap.size() > maxHeap.size()) {
            maxHeap.push(minHeap.top());
            minHeap.pop();
        }
    }
    
    double findMedian() {
        if (maxHeap.empty()) {
            return 0.0;
        }
        
        if (maxHeap.size() == minHeap.size()) {
            return (maxHeap.top() + minHeap.top()) / 2.0;
        } else {
            return static_cast<double>(maxHeap.top());
        }
    }
    
    // 获取数据流大小
    size_t size() const {
        return maxHeap.size() + minHeap.size();
    }
};

// 使用示例
int main() {
    MedianFinder finder;
    std::vector<int> data = {1, 3, 2, 5, 4, 6, 7};
    
    std::cout << "实时数据流中位数:" << std::endl;
    for (int num : data) {
        finder.addNum(num);
        std::cout << "添加 " << num << " -> 中位数: " << finder.findMedian() 
                  << " (总数据量: " << finder.size() << ")" << std::endl;
    }
    
    return 0;
}