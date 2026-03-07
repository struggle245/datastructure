#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <atomic>

class InfiniteAlternatePrinter {
private:
    std::mutex mtx;
    std::condition_variable cv;
    bool printABC = true;
    std::atomic<bool> stopFlag{false};
    
public:
    void printABCThread() {
        std::string abc = "abc";
        int index = 0;
        
        while (!stopFlag) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return printABC || stopFlag; });
            if (stopFlag) break;
            
            std::cout << abc[index] << " ";
            index = (index + 1) % abc.length();
            
            printABC = false;
            cv.notify_one();
            
            // 稍微延迟，方便观察
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    void print123Thread() {
        std::string numbers = "123";
        int index = 0;
        
        while (!stopFlag) {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait(lock, [this] { return !printABC || stopFlag; });
            if (stopFlag) break;
            
            std::cout << numbers[index] << " ";
            index = (index + 1) % numbers.length();
            
            printABC = true;
            cv.notify_one();
            
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
    
    void stop() {
        stopFlag = true;
        cv.notify_all();
    }
};

int main() {
    InfiniteAlternatePrinter printer;
    
    std::thread t1(&InfiniteAlternatePrinter::printABCThread, &printer);
    std::thread t2(&InfiniteAlternatePrinter::print123Thread, &printer);
    
    // 运行5秒后停止
    std::this_thread::sleep_for(std::chrono::seconds(5));
    printer.stop();
    
    t1.join();
    t2.join();
    
    std::cout << "\n程序结束" << std::endl;
    return 0;
}