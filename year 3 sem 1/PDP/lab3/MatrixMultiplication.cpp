#include <iostream>
#include <vector>
#include <thread>
#include <functional>
#include <chrono>
#include <stdio.h>
#include <stdint.h>
#include <atomic>
#include <thread>
#include <vector>
#include <mutex>
#include <algorithm>
#include <functional>
#include <condition_variable>
#include <list>

// 3 matrices using vectors: A, B, C; all have the dimensions; C is 0 initialized; A and B are 1s all over
int n = 500;
// std::vector<std::vector<int>> A = {
//     {9, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 9}
// };
// std::vector<std::vector<int>> B = {
//     {9, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 1},
//     {1, 1, 1, 1, 1, 1, 1, 1, 9}
// };
// std::vector<std::vector<int>> C = {
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0},
//     {0, 0, 0, 0, 0, 0, 0, 0, 0}
// };

// make the matrices depend on `n`
std::vector<std::vector<int>> A(n, std::vector<int>(n, 1));
std::vector<std::vector<int>> B(n, std::vector<int>(n, 1));
std::vector<std::vector<int>> C(n, std::vector<int>(n, 0));

struct Task {
    std::vector<std::pair<int, int>> elements; // (i, j) pairs for C matrix positions
};

class ThreadPool {
public:
    explicit ThreadPool(size_t nrThreads)
        :m_end(false)
    {
        m_threads.reserve(nrThreads);
        for (size_t i = 0; i < nrThreads; ++i) {
            m_threads.emplace_back([this]() {this->run(); });
        }
    }

    ~ThreadPool() {
        close();
        for (std::thread& t : m_threads) {
            t.join();
        }
    }

    void close() {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_end = true;
        m_cond.notify_all();
        // for (std::thread& t : m_threads) {
        //     t.join();
        // }
    }

    void enqueue(std::function<void()> func) {
        std::unique_lock<std::mutex> lck(m_mutex);
        m_queue.push_back(std::move(func));
        m_cond.notify_one();
    }

    //    template<typename Func, typename... Args>
    //    void enqueue(Func func, Args&&... args) {
    //        std::function<void()> f = [=](){func(args...);};
    //        enqueue(std::move(f));
    //    }
    private:
        void run() {
            while (true) {
                std::function<void()> toExec;
                {
                    std::unique_lock<std::mutex> lck(m_mutex);
                    while (m_queue.empty() && !m_end) {
                        m_cond.wait(lck);
                    }
                    if (m_queue.empty()) {
                        return;
                    }
                    toExec = std::move(m_queue.front());
                    m_queue.pop_front();
                }
                toExec();
            }
        }

    std::mutex m_mutex;
    std::condition_variable m_cond;
    std::list<std::function<void()> > m_queue;
    bool m_end;
    std::vector<std::thread> m_threads;
};

void printMatrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }
}

void multiplyElement(const Task& task) {
    for (const auto [i, j] : task.elements) {
        for (int k = 0; k < n; ++k) {
            C[i][j] += A[i][k] * B[k][j];
        }
    }
}

void threadWorker(Task task) {
    multiplyElement(task);
}

void multiplyWithTasks(const std::vector<Task>& tasks) {
    std::vector<std::thread> threads;
    for (const auto& task : tasks) {
        threads.emplace_back(threadWorker, task);
    }
    for (auto& t : threads) {
        t.join();
    }
}

std::vector<Task> divideTasksRowByRow(int n, int numTasks) {
    std::vector<Task> tasks(numTasks);

    int elementsPerTask = (n * n) / numTasks;
    int extraElements = (n * n) % numTasks; // In this case, 1 extra element for the last task

    int currentRow = 0, currentCol = 0;
    
    for (int taskID = 0; taskID < numTasks; ++taskID) {
        int elementsForThisTask = elementsPerTask + (taskID == numTasks - 1 ? extraElements : 0);
        
        for (int count = 0; count < elementsForThisTask; ++count) {
            tasks[taskID].elements.emplace_back(currentRow, currentCol);
            
            // Move to the next element in row-major order
            currentCol++;
            if (currentCol == n) { // Move to the next row if end of row is reached
                currentCol = 0;
                currentRow++;
            }
        }
    }
    return tasks;
}

std::vector<Task> divideTasksColumnByColumn(int n, int numTasks) {
    std::vector<Task> tasks(numTasks);

    int elementsPerTask = (n * n) / numTasks;
    int extraElements = (n * n) % numTasks; // 1 extra element for the last task

    int currentCol = 0, currentRow = 0;
    
    for (int taskID = 0; taskID < numTasks; ++taskID) {
        int elementsForThisTask = elementsPerTask + (taskID == numTasks - 1 ? extraElements : 0);
        
        for (int count = 0; count < elementsForThisTask; ++count) {
            tasks[taskID].elements.emplace_back(currentRow, currentCol);

            // Move to the next element in column-major order
            currentRow++;
            if (currentRow == n) { // Move to the next column if end of column is reached
                currentRow = 0;
                currentCol++;
            }
        }
    }
    return tasks;
}

std::vector<Task> divideTasksByKthElement(int n, int numTasks) {
    std::vector<Task> tasks(numTasks);

    for (int i = 0; i < n; ++i) {         // Traverse rows
        for (int j = 0; j < n; ++j) {     // Traverse columns
            int taskID = (i * n + j) % numTasks; // Assign based on position's modulus with numTasks
            tasks[taskID].elements.emplace_back(i, j);
        }
    }
    return tasks;
}

void printTasks(const std::vector<Task>& tasks) {
    for (int taskID = 0; taskID < tasks.size(); ++taskID) {
        std::cout << "Task " << taskID << ": ";
        for (const auto& [i, j] : tasks[taskID].elements) {
            std::cout << "(" << i << "," << j << ") ";
        }
        std::cout << "\n";
    }
}

int main() {
    int numTasks = 30;
    int numThreads = 12;

    // Row-major multiplication
    std::cout << "Row-Major Task Division:\n";
    auto rowTasks = divideTasksRowByRow(n, numTasks);
    auto start = std::chrono::high_resolution_clock::now();
    multiplyWithTasks(rowTasks);
    auto end = std::chrono::high_resolution_clock::now();
    //printMatrix(C);
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by Row-Major Task Division: " << duration << " microseconds\n";

    // Reset matrix C for next multiplication
    C.assign(n, std::vector<int>(n, 0));

    // Column-major multiplication
    std::cout << "\nColumn-Major Task Division:\n";
    auto colTasks = divideTasksColumnByColumn(n, numTasks);
    start = std::chrono::high_resolution_clock::now();
    multiplyWithTasks(colTasks);
    end = std::chrono::high_resolution_clock::now();
    //printMatrix(C);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by Column-Major Task Division: " << duration << " microseconds\n";

    // Reset matrix C for next multiplication
    C.assign(n, std::vector<int>(n, 0));

    // K-th element multiplication
    std::cout << "\nK-th Element Task Division:\n";
    auto kthTasks = divideTasksByKthElement(n, numTasks);
    start = std::chrono::high_resolution_clock::now();
    multiplyWithTasks(kthTasks);
    end = std::chrono::high_resolution_clock::now();
    //printMatrix(C);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by K-th Element Task Division: " << duration << " microseconds\n";
    
    // Now, using a thread pool
    ThreadPool* poolRows = new ThreadPool(numThreads);
    start = std::chrono::high_resolution_clock::now();
    for(const auto& task : rowTasks) {
        poolRows->enqueue([task](){multiplyElement(task);});
    }
    poolRows->close();
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by row ThreadPool: " << duration << " microseconds\n";
    //delete &poolRows;
    std::destroy_at(poolRows);

    ThreadPool* poolCols = new ThreadPool(numThreads);
    //ThreadPool poolCols(numThreads);
    start = std::chrono::high_resolution_clock::now();
    for(const auto& task : colTasks) {
        poolCols->enqueue([task](){multiplyElement(task);});
    }
    poolCols->close();
    end = std::chrono::high_resolution_clock::now();
    // delete &poolCols;
    std::destroy_at(poolCols);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by column ThreadPool: " << duration << " microseconds\n";

    //ThreadPool poolKth(numThreads);
    ThreadPool* poolKth = new ThreadPool(numThreads);
    start = std::chrono::high_resolution_clock::now();
    for(const auto& task : kthTasks) {
        poolKth->enqueue([task](){multiplyElement(task);});
    }
    poolKth->close();
    end = std::chrono::high_resolution_clock::now();
    std::destroy_at(poolKth);
    duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    std::cout << "Time taken by kth ThreadPool: " << duration << " microseconds\n";
    //delete &poolKth;



    return 0;
}