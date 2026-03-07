#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

class AlternatePrinter {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool printABC = true;  // 控制打印顺序的标志
    
public:
    void printABCThread() {
        std::string abc = "abc";
        int index = 0;
        
        for (int i = 0; i < 3; ++i) {  // 每个字母打印3次
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return printABC; });
            
            std::cout << abc[index] << " ";
            index = (index + 1) % abc.length();
            
            printABC = false;
            cv.notify_one();
        }
    }
    
    void print123Thread() {
        std::string numbers = "123";
        int index = 0;
        
        for (int i = 0; i < 3; ++i) {  // 每个数字打印3次
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !printABC; });
            
            std::cout << numbers[index] << " ";
            index = (index + 1) % numbers.length();
            
            printABC = true;
            cv.notify_one();
        }
    }
};

int main() {
    AlternatePrinter printer;
    
    std::thread t1(&AlternatePrinter::printABCThread, &printer);
    std::thread t2(&AlternatePrinter::print123Thread, &printer);
    
    t1.join();
    t2.join();
    
    std::cout << std::endl;
    return 0;
}