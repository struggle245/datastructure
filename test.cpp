#include<iostream>

using namespace std;

class singleton
{
public:
    static singleton& getInst()
    {
        static singleton singleton;
        return singleton;
    }
private:
    singleton(){}
    singleton(const singleton& singleton)=delete;
    singleton &operator=(const singleton& singleton)=delete;

};

class singletonHungry
{
private:
    singletonHungry(){};
    singletonHungry(const singletonHungry& singleton1)=delete;
    singletonHungry& operator=(const singletonHungry&)=delete;
public:
    static singletonHungry* getInst()
    {
        return &single;
    }
private:
    static singletonHungry single;
};
singletonHungry singletonHungry::single;
int main()
{
    singleton& singleton=singleton::getInst();
    //cout<<singleton<<endl;

    return 0;
}