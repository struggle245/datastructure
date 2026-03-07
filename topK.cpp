#include<iostream>
#include<queue>
#include<vector>
using namespace std;
int main()
{
    vector<int> vec;
    srand(time(nullptr));

    for(int i=0;i<1000;i++)
    {
        vec.push_back(i);
    }
    priority_queue<int> maxheap;//大根堆来求最小的topk
 //小根堆来求最大的topk
    int k=5;
    for(int i=0;i<5;i++)
    {
        maxheap.push(vec[i]);
    }
    for(int i=5;i<vec.size();i++)
    {
        if(maxheap.top()>vec[i])
        {
            maxheap.pop();
            maxheap.push(vec[i]);
        }
    }
    while(!maxheap.empty())
    {
        cout<<maxheap.top()<<endl;
        maxheap.pop();
    }
    return 0;
}