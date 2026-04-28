#include<iostream>
using namespace std;

int partation(int arr[],int l,int r)
{
    int pivot=arr[l];
    while(l<r)
    {
        while (l<r&&pivot<arr[r])
        {
            r--;
        }
        if(l<r)
        {
            arr[l]=arr[r];
            l++;
        }
        while(l<r&&pivot>arr[l])
        {
            l++;
        }
        if(l<r)
        {
            arr[r]=arr[l];
            r--;
        }
     
    }
    arr[l]=pivot;
    return l;
   
}

void quicksort(int arr[],int begin,int end)
{
    if(begin>end)
    {
        return;
    }
    
    int positon=partation(arr,begin,end);
    quicksort(arr,begin,positon-1);
    quicksort(arr,positon+1,end);
    
}

// 打印数组函数
void printArray(int arr[],int size) {
    for (int i=0;i<size;i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 测试示例
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "原始数组: ";
    printArray(arr,size);
    
    quicksort(arr,0,size-1);
    
    cout << "排序后数组: ";
    printArray(arr,size);
    //hello
    
    return 0;
}