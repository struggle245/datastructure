#include<iostream>
using namespace std;

void merge(int arr[],int l,int m,int r)
{
    int *p=new int[r-l+1];
    int idx=0;
    int i=l;
    int j=m+1;
    while(i<=m&&j<=r)
    {
        if(arr[i]<arr[j])
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

void mergesort(int arr[],int l,int r)
{
    if(l>=r)return ;
    int m=(l+r)/2;
    mergesort(arr,l,m);
    mergesort(arr,m+1,r);
    merge(arr,l,m,r);
}

int main()
{
    int arr[]={64, 34, 25, 12, 22, 11, 90};
    int size=sizeof(arr)/sizeof(arr[0]);
    mergesort(arr,0,size-1);
    for(int i=0;i<size;i++)
    {
       
        cout << arr[i] << " ";
        
    }
    cout<<endl;
    
    
    return 0;
}