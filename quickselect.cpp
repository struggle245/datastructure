#include<iostream>
#include<map>
#include<vector>
using namespace std;

int partition(vector<int>& arr,int begin,int end)
{
    int pivot=arr[begin];
    while(begin<end)
    {
        while (begin<end&&arr[end]>pivot)
        {
            end--;
        }
        if(begin<end&&arr[end]<pivot)
        { 
            arr[begin]=arr[end];
            begin++;
        }
        while(begin<end&&arr[begin]<pivot)
        {
            begin++;
        }
        if(begin<end&&arr[begin]>pivot)
        {
            arr[end]=arr[begin];
            end--;
        }
    }
    arr[begin]=pivot;
    return begin;
}
void quicksort(vector<int>& arr, int begin, int end) {
    if(begin>end)
    {
        return;
    }
    int pos=partition(arr,begin,end);
    quicksort(arr,begin,pos-1);
    quicksort(arr,pos+1,end);
}
void quickselect(vector<int>& arr, int begin, int end,int k)
{
    if(begin>end)
    {
        return ;
    }
    int pos=partition(arr,begin,end);
    
    if(pos==k-1)
    {
        return ;
    }else if(pos<k-1)
    {
        quickselect(arr,pos+1,end,k);
    }else{
        quickselect(arr,begin,pos-1,k);
    }
    
}
class Trie
{
public:
    Trie():root_(new TrieNode('\0',0)){}
private:
   struct TrieNode
    {
        TrieNode(char ch,int freq):ch_(ch),freq_(freq){}
        char ch_;
        int freq_;
        map<char,TrieNode*> nodeMap_;
    };
  
    TrieNode* root_; 
};
int main()
{
    vector<int> vec{1,2,8,5,7,9};
    for(int num:vec)
    {
        cout<<num<<" ";
        
    }
    cout<<"===="<<endl;
   quickselect(vec,0,vec.size()-1,3);
   for(int i=0;i<3;i++)
   {
        cout<<vec[i]<<" ";
   }
    return 0;
}