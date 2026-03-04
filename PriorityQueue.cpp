#include<iostream>
#include<functional>
#include<stdlib.h>
#include<cstring>
#include<time.h>
using namespace std;
class PriorityQueue
{
public:
    using Comp=function<bool(int,int)>;
    PriorityQueue(int cap=20,Comp comp=greater<int>())
        :size_(0)
        ,cap_(cap)
        ,comp_(comp)
    {
        que_=new int[cap];
    }
    PriorityQueue()
        :size_(0)
        ,cap_(20)
        ,comp_(greater<int>())
    {
        que_=new int[cap_];
    }
    ~PriorityQueue()
    {
        delete []que_;
        que_=nullptr;

    }
public:
        void push(int val)
        {
            if(size_==cap_)
            {
                int* p=new int[2*cap_];
                memcpy(p,que_,cap_*sizeof(int));
                delete[] que_;
                que_=p;
                cap_*=2;
                
            }
            if(size_==0)
            {
                que_[size_]=val;
                
            }else
            {
                siftUp(size_,val);
            }
            size_++;

        }
        void pop()
        {
            if(size_==0)
            {
                throw"container is empty";
            }
            size_--;
            if(size_>0)
            {
                siftDown(0,que_[size_]);
            }
        }
        bool empty ()const{return size_==0;}
        int top(){
            return que_[0];
        }
private:
    void siftUp(int i,int val)
    {
        while(i>0)
        {
            int father=(i-1)/2;
            if(comp_(val,que_[father]))
            {
                que_[i]=que_[father];
                i=father;
            }
            else{
                break;
            }
        }
        que_[i]=val;
    }
    void siftDown(int i,int val)
    {
        while(i<=(size_-1)/2)
        {
            int child=2*i+1;
            if(child+1<size_&&comp_(que_[child+1],que_[child]))
            {
                child=child+1;
            }
            if(comp_(que_[child],val))
            {
                que_[i]=que_[child];
                i=child;
            }
            else{
                break;
            }
          
        }
          que_[i]=val;
    }
    int* que_;
    int size_;
    int cap_;
    Comp comp_;

};

int main()
{
    srand(time(NULL));
    PriorityQueue que;
    for(int i=0;i<10;i++)
    {
        que.push(rand()%100);
    }
    //nihao
    return 0;
}