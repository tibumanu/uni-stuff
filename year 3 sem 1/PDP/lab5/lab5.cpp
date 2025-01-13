#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>
#include <cassert>
#include <algorithm>
#include <cmath>


void printPoly(const std::vector<int> &poly, const std::string &label = "")
{
    if (!label.empty())
    {
        std::cout << label + ": " << "\n";
    }
    for (size_t i = 0; i < poly.size(); ++i)
    {
        std::cout << poly[i] << "x^" << i;
        if (i != poly.size() - 1)
        {
            std::cout << " + ";
        }
    }
    std::cout << std::endl;
}


// poly1 + poly2
std::vector<int> addPoly(const std::vector<int> &poly1, const std::vector<int> &poly2)
{
    const auto &maxPoly = poly1.size() > poly2.size() ? poly1 : poly2;
    const auto &minPoly = maxPoly == poly1 ? poly2 : poly1;
    std::vector<int> res(maxPoly);
    for (size_t i = 0; i < minPoly.size(); ++i)
    {
        res[i] += minPoly[i];
    }
    return res;
}


// poly1 - poly2
std::vector<int> subPoly(const std::vector<int> &poly1, const std::vector<int> &poly2)
{
    std::vector<int> res(poly1);
    size_t i;
    for (i = 0; i < std::min(poly1.size(), poly2.size()); ++i)
    {
        res[i] -= poly2[i];
    }
    res.resize(std::max(poly1.size(), poly2.size()));
    for (; i < poly2.size(); ++i)
    {
        res[i] = -poly2[i];
    }
    // trim zeroes at the end
    while (res.size() > 1 && res.back() == 0)
    {
        res.pop_back();
    }
    return res;
}


// shift by n: x^k becomes x^(k + n)
std::vector<int> shiftPoly(const std::vector<int> &poly, const int n)
{
    std::vector<int> res(poly.size() + n, 0);
    for (int i = (int)res.size() - 1; i - n >= 0; --i)
    {
        res[i] = poly[i - n];
    }
    return res;
}


// O(n^2) sequential multiplication
std::vector<int> regularSequential(const std::vector<int> &A, const std::vector<int> &B)
{
    std::vector<int> result(A.size() + B.size() - 1, 0);
    for (size_t i = 0; i < A.size(); ++i)
    {
        for (size_t j = 0; j < B.size(); ++j)
        {
            result[i + j] += A[i] * B[j];
        }
    }
    return result;
}


// O(n^2) parallel multiplication
std::vector<int> regularParallel(const std::vector<int> &A, const std::vector<int> &B)
{
    std::vector<int> result(A.size() + B.size() - 1, 0);
    std::mutex mtx;

    auto worker = [&](const int start, const int end)
    {
        for (int i = start; i < end; ++i)
        {
            for (size_t j = 0; j < B.size(); ++j)
            {
                std::lock_guard<std::mutex> lock(mtx);
                result[i + j] += A[i] * B[j];
            }
        }
    };

    const int numThreads = 12;
    const size_t chunkSize = A.size() / numThreads;
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t)
    {
        const size_t start = t * chunkSize;
        const size_t end = (t == numThreads - 1) ? A.size() : start + chunkSize;
        threads.emplace_back(worker, start, end);
    }
    for (auto &th : threads)
    {
        th.join();
    }
    return result;
}


// Karatsuba Sequential Multiplication
std::vector<int> karatsubaSequential(const std::vector<int> &A, const std::vector<int> &B)
{
    const int maxSize = (int)std::max(A.size(), B.size());
    const int n = maxSize + maxSize % 2;
    // const int paddedSize = (int)std::pow(2, std::ceil(std::log2(maxSize)));
    if (n <= 100)
    {
        return regularSequential(A, B);
    }

    const int half = n / 2;
    std::vector<int> A_low(A.begin(), A.begin() + half);
    std::vector<int> A_high(A.begin() + half, A.end());
    std::vector<int> B_low(B.begin(), B.begin() + half);
    std::vector<int> B_high(B.begin() + half, B.end());

    std::vector<int> z0 = karatsubaSequential(A_low, B_low);
    std::vector<int> z1 = karatsubaSequential(addPoly(A_low, A_high), addPoly(B_low, B_high));
    std::vector<int> z2 = karatsubaSequential(A_high, B_high);

    const auto term1 = shiftPoly(z2, n);
    const auto term2 = shiftPoly(subPoly(subPoly(z1, z2), z0), half);
    const auto term3 = z0;
    return addPoly(addPoly(term1, term2), term3);
}


std::vector<int> karatsubaParallel(const std::vector<int> &A, const std::vector<int> &B)
{
    const int maxSize = (int)std::max(A.size(), B.size());
    const int n = maxSize + maxSize % 2;
    // const int paddedSize = (int)std::pow(2, std::ceil(std::log2(maxSize)));
    if (n <= 100)
    {
        return karatsubaSequential(A, B);
    }

    const int half = n / 2;
    std::vector<int> A_low(A.begin(), A.begin() + half);
    std::vector<int> A_high(A.begin() + half, A.end());
    std::vector<int> B_low(B.begin(), B.begin() + half);
    std::vector<int> B_high(B.begin() + half, B.end());

    std::vector<int> z0, z1, z2;
    std::thread t1([&]() { z0 = karatsubaParallel(A_low, B_low); });
    std::thread t2([&]() { z1 = karatsubaParallel(addPoly(A_low, A_high), addPoly(B_low, B_high)); });
    std::thread t3([&]() { z2 = karatsubaParallel(A_high, B_high); });

    t1.join();
    t2.join();
    t3.join();

    const auto term1 = shiftPoly(z2, n);
    const auto term2 = shiftPoly(subPoly(subPoly(z1, z2), z0), half);
    const auto term3 = z0;
    return addPoly(addPoly(term1, term2), term3);
}


template <typename Func>
void measureTime(Func func, const std::vector<int> &A, const std::vector<int> &B, const std::string &label)
{
    auto start = std::chrono::high_resolution_clock::now();
    const auto resPoly = func(A, B);
    auto end = std::chrono::high_resolution_clock::now();
    // printPoly(resPoly);

    std::cout << label << ": " << std::chrono::duration<double, std::milli>(end - start).count() << " ms" << std::endl;
}


int main()
{
    std::vector<int> A, B;
    const int size = 20000;
    for (int i = 1; i <= size; ++i)
    {
        A.emplace_back(i);
        B.emplace_back(size + 1 - i);
    }

    measureTime(regularSequential, A, B, "regular: sequential");
    measureTime(regularParallel, A, B, "regular: parallelized");
    measureTime(karatsubaSequential, A, B, "karatsuba: sequential");
    measureTime(karatsubaParallel, A, B, "karatsuba: parallelized");
}
