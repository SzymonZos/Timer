#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>

template<typename T = std::chrono::milliseconds>
class Timer {
public:
    Timer() : startTimePoint_{std::chrono::high_resolution_clock::now()} {}

    ~Timer() {
        StopTimer();
    }

    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;

    Timer(Timer&& other) = delete;
    Timer& operator=(Timer&& other) = delete;

private:
    std::chrono::time_point<std::chrono::high_resolution_clock>
        startTimePoint_;

    void StopTimer() {
        const auto endTimePoint = std::chrono::high_resolution_clock::now();
        const auto start = std::chrono::time_point_cast<T>(startTimePoint_)
                               .time_since_epoch()
                               .count();
        const auto end = std::chrono::time_point_cast<T>(endTimePoint)
                             .time_since_epoch()
                             .count();
        PrintTime(start, end);
    }

    template<typename Count>
    void PrintTime(Count start, Count end);
};

template<>
template<typename Count>
void Timer<std::chrono::nanoseconds>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: "
              << static_cast<double>(end - start) / 1000.0 << " us  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::microseconds>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: "
              << static_cast<double>(end - start) / 1000.0 << " ms  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::milliseconds>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: "
              << static_cast<double>(end - start) / 1000.0 << " s  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::seconds>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: " << end - start << " s  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::minutes>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: " << end - start << " min  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::hours>::PrintTime(Count start, Count end) {
    std::cout << "Elapsed time: " << end - start << " h  \n";
}

#endif // TIMER_HPP
