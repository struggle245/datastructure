#include<iostream>
using namespace std;

void siftDown(int arr[],int i,int size)
{
    int val=arr[i];
     while(i<size/2)
     {
        int child=2*i+1;
        if(child+1<size&&arr[child+1]>arr[child])
        {
            child=child+1;
        }
        if(arr[child]>val)
        {
            arr[i]=arr[child];
            i=child;

        }
        else{
            break;
        }
     }
     arr[i]=val;
}
void heapSort(int arr[],int size)
{
    //最后一个节点坐标，要从第一个非叶子节点开始进行下沉调整，从第一个非叶子节点开始进行调整到根节点
    int end=size-1;
    for(int i=(end-1)/2;i>=0;i--)
    {
        siftDown(arr,i,size);
    }
    //把堆顶元素和末尾元素交换，再进行下沉调整
    for(int i=end;i>=0;i--)
    {
        int tmp=arr[0];
        arr[0]=arr[i];
        arr[i]=tmp;
        siftDown(arr,0,i);

    }
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
    int arr[] = {64, 34, 25, 9, 22, 11, 90};
    int size = sizeof(arr) / sizeof(arr[0]);
    cout << "原始数组: ";
    printArray(arr,size);
    
    heapSort(arr,size);
    
    cout << "排序后数组: ";
    printArray(arr,size);
    
    return 0;
}
