#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <thread>
#include <iostream>
#include <functional>

typedef pthread_mutex_t Mutex;
typedef pthread_t Thread;

// globals
int arrA[100], arrB[100];
int sum = 0;
std::mutex mtx;
std::condition_variable cv;
bool ready = false;



// Sync Queue
class SyncQueue{
    private:
        std::queue<int> q;
        std::mutex m;
        int capacity;
    public:
        SyncQueue(int capacity){
            this->capacity = capacity;
            this->q = std::queue<int>();            
        }
        bool empty(){
            m.lock();
            bool res = q.empty();
            m.unlock();
            return res;
        }

        bool full(){
            m.lock();
            bool res = q.size() == capacity;
            m.unlock();
            return res;
        }

        void enqueue(int item){
            m.lock();
            if(q.size() == capacity){
                m.unlock();
                throw std::runtime_error("Queue is full");
                return;
            }
            q.push(item);
            m.unlock();
        }

        int dequeue(){
            m.lock();
            if(q.empty()){
                m.unlock();
                throw std::runtime_error("Queue is empty");
            }
            int item = q.front();   q.pop();
            m.unlock();
            return item;
        }

        void close(){
            std::unique_lock<std::mutex> lock(m);

        }
    };

// void waitForSignal(){
//     std::unique_lock<std::mutex> lock(mtx);
//     while(!ready)   cv.wait(lock);
//     std::cout << "Signal received\n";
// }

void waitForSignal(std::function<bool()> predicate) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, predicate);
    std::cout << "Signal received\n";
}

void sendSignal(){
    {
        std::lock_guard<std::mutex> lock(mtx);
        ready = true;
    }
    cv.notify_all();
}

void producer(SyncQueue *q){
    for(int i = 0; i < 100; i++){
        waitForSignal([&q] { return !q->full(); });
        q->enqueue(arrA[i] * arrB[i]);
        std::cout << "Produced item: " << arrA[i] * arrB[i] << std::endl;
        // ready = true;
        // lock.unlock();
        // cv.notify_all();
        sendSignal();
    }
}

void consumer(SyncQueue *q){

    for(int i = 0; i < 100; i++){
        waitForSignal([&q] { return !q->empty(); });
        int item = q->dequeue();
        std::cout << "Consumed item: " << item << std::endl;
        sum += item;
        // lock.unlock();
        // cv.notify_all();
        sendSignal();
    }
}

int main(){
    for(int i = 0; i < 100; i++){
    //arrA[i] = i+1; arrB[i] = (i+1)*(i+1);// the dot product (`sum`) should be 25502500 = sum of (i+1) * ((i+1)^2) for i = 0, 99
    arrA[i] = i+1; arrB[i] = i+1; // the dot product (`sum`) should be 171700
    }
    SyncQueue q(5);
    std::thread producerThread(producer, &q);
    std::thread consumerThread(consumer, &q);

    producerThread.join();
    consumerThread.join();

    std::cout << "Sum: " << sum << std::endl;
    return 0;
}