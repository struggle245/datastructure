#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>

class ProducerConsumer {
private:
    std::queue<int> buffer;
    const size_t max_size;
    std::mutex mtx;
    std::condition_variable not_full;  // 缓冲区不满的条件变量
    std::condition_variable not_empty; // 缓冲区不空的条件变量
    bool stop;

public:
    ProducerConsumer(size_t size) : max_size(size), stop(false) {}

    void producer(int id, int items_to_produce) {
        for (int i = 0; i < items_to_produce; ++i) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // 等待缓冲区不满
            not_full.wait(lock, [this]() { 
                return buffer.size() < max_size || stop; 
            });
            
            if (stop) break;
            
            int item = i + id * 1000;  // 生成唯一的产品ID
            buffer.push(item);
            std::cout << "Producer " << id << " produced item: " << item 
                      << " (buffer size: " << buffer.size() << ")" << std::endl;
            
            lock.unlock();
            not_empty.notify_one();  // 通知消费者
            
            // 模拟生产耗时
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
        std::cout << "Producer " << id << " finished." << std::endl;
    }

    void consumer(int id, int items_to_consume) {
        int consumed = 0;
        while (consumed < items_to_consume) {
            std::unique_lock<std::mutex> lock(mtx);
            
            // 等待缓冲区不空
            not_empty.wait(lock, [this]() { 
                return !buffer.empty() || stop; 
            });
            
            if (stop && buffer.empty()) break;
            
            int item = buffer.front();
            buffer.pop();
            consumed++;
            std::cout << "Consumer " << id << " consumed item: " << item 
                      << " (buffer size: " << buffer.size() << ")" << std::endl;
            
            lock.unlock();
            not_full.notify_one();  // 通知生产者
            
            // 模拟消费耗时
            std::this_thread::sleep_for(std::chrono::milliseconds(150));
        }
        std::cout << "Consumer " << id << " finished." << std::endl;
    }

    void stop_all() {
        std::lock_guard<std::mutex> lock(mtx);
        stop = true;
        not_full.notify_all();
        not_empty.notify_all();
    }
};

int main() {
    const size_t BUFFER_SIZE = 5;
    const int NUM_PRODUCERS = 2;
    const int NUM_CONSUMERS = 3;
    const int ITEMS_PER_PRODUCER = 10;
    const int ITEMS_PER_CONSUMER = 7;

    ProducerConsumer pc(BUFFER_SIZE);
    
    std::vector<std::thread> producers;
    std::vector<std::thread> consumers;

    // 创建生产者线程
    for (int i = 0; i < NUM_PRODUCERS; ++i) {
        producers.emplace_back(&ProducerConsumer::producer, &pc, i, ITEMS_PER_PRODUCER);
    }

    // 创建消费者线程
    for (int i = 0; i < NUM_CONSUMERS; ++i) {
        consumers.emplace_back(&ProducerConsumer::consumer, &pc, i, ITEMS_PER_CONSUMER);
    }

    // 等待生产者完成
    for (auto& p : producers) {
        p.join();
    }

    // 停止所有线程
    pc.stop_all();

    // 等待消费者完成
    for (auto& c : consumers) {
        c.join();
    }

    std::cout << "All threads finished." << std::endl;
    return 0;
}