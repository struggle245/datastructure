#include <iostream>
#include <vector>
using namespace std;

// 冒泡排序函数
void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    //64, 34, 25, 12, 22, 11,
    // 外层循环控制排序轮数
    for (int i = 0; i < n - 1; i++) {
        // 标志位，用于优化：如果一轮中没有发生交换，说明已经有序
        bool swapped = false;
        
        // 内层循环进行相邻元素比较和交换
        // 每轮结束后，最大的元素会"冒泡"到末尾
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // 交换相邻元素
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        
        // 如果本轮没有发生交换，说明数组已经有序，提前结束
        if (!swapped) {
            break;
        }
    }
}

// 打印数组函数
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // 测试示例
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "原始数组: ";
    printArray(arr);
    
    bubbleSort(arr);
    
    cout << "排序后数组: ";
    printArray(arr);
    
    return 0;
}