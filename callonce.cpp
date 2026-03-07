#include<iostream>

using namespace std;
//通过静态成员变量实现单例
//懒汉式
class Single2
{
private:
    Single2()
    {

    }
    Single2(const Single2 &) = delete;
    Single2 &operator=(const Single2 &) = delete;
public:
    static Single2 &GetInst()
    {
        static Single2 single;
        return single;
    }
};

//饿汉式
class Single2Hungry
{
private:
    Single2Hungry()
    {
    }
    Single2Hungry(const Single2Hungry &) = delete;
    Single2Hungry &operator=(const Single2Hungry &) = delete;
public:
    static Single2Hungry *GetInst()
    {
        if (single == nullptr)
        {
            single = new Single2Hungry();
        }
        return single;
    }
private:
    static Single2Hungry *single;
};
int main()
{
    Single2& single=Single2::GetInst();
    return 0;
}