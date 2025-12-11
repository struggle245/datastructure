#include<iostream>
#include<vector>
using namespace std;

void insertsort(vector<int>&arr)
{
    for(int i=1;i<arr.size();i++)
    {
        int val=arr[i];
        int j=i-1;
        for(;j>=0;j--)
        {
            if(arr[j]<=val)break;
            arr[j+1]=arr[j];
        }
        arr[j+1]=val;
    }
}
// 打印数组函数
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}
int main()
{
 // 测试示例
    vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    cout << "原始数组: ";
    printArray(arr);
    
    insertsort(arr);
    
    cout << "排序后数组: ";
    printArray(arr);
    return 0;
}