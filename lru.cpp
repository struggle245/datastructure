#include<iostream>
#include<unordered_map>
using namespace std;
struct Node{
    int key_;
    int val_;
    Node* next;
    Node* prev;
    Node(int key=0,int val=0):key_(key),val_(val),next(nullptr),prev(nullptr){}
};

class LRUCache{
public:
    LRUCache(int capacity):dummyhead(new Node()),capacity(capacity)
    {
        dummyhead->next=dummyhead;
        dummyhead->prev=dummyhead;
    }
    int get(int key)
    {
        Node* node=get_node(key);
        return node?node->val_:-1;
    }
    void put(int key,int val)
    {
        Node* node=get_node(key);
        if(node)
        {
            node->val_=val;
            return ;
        }
        node=new Node(key,val);
        key_to_node[key]=node;
        push_front(node);
        if(key_to_node.size()>capacity)
        {
            Node* back_node=dummyhead->prev;
            key_to_node.erase(back_node->key_);
            remove(back_node);
            delete back_node;
        }
        
    }
private:
    int capacity;
    Node* dummyhead;
    unordered_map<int,Node*> key_to_node;
    Node* get_node(int key)
    {
        auto it=key_to_node.find(key);
        if(it==key_to_node.end())
        {
            return nullptr;
        }
        Node* node=it->second;
        remove(node);
        push_front(node);
        return node;
    }
    void remove(Node* node)
    {
        node->prev->next=node->next;
        node->next->prev=node->prev;
    }
    void push_front(Node* node)
    {
        node->prev=dummyhead;
        node->next=dummyhead->next;
        dummyhead->next->prev=node;
        dummyhead->next=node;
    }
};
int main()
{
    LRUCache lru(2);
    lru.put(1,3);
    lru.put(2,4);
    lru.put(3,5);
    cout<<lru.get(1)<<endl;
    cout<<lru.get(2)<<endl;
    cout<<lru.get(3)<<endl;
    return 0;
}