#include<iostream>
#include<vector>

using namespace std;

void Merge(int arr[],int l,int m,int r)
{
    int* p=new int[r-l+1];
    int idx=0;
    int i=l;
    int j=m+1;


    while(i<=m&&j<=r)
    {
        if(arr[i]<=arr[j])
        {
            p[idx++]=arr[i++];
        }else{
            p[idx++]=arr[j++];
        }

    }
    while(i<=m)
    {
        p[idx++]=arr[i++];
    }
    while(j<=r)
    {
        p[idx++]=arr[j++];
    }

    for(int i=0;i<idx;i++)
    {
        arr[l+i]=p[i];
    }
    delete[] p;
}

void MergeSort(int arr[],int begin,int end)
{
    //递归结束的条件
    if(begin>=end)
    {
        return;
    }
    int mid=(begin+end)/2;
    //先递
    MergeSort(arr,begin,mid);
    MergeSort(arr,mid+1,end);
    //再归并
    Merge(arr,begin,mid,end);


}
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
    

    MergeSort(arr,0,size-1);

    
    cout << "排序后数组: ";
    printArray(arr,size);
    
    return 0;
}