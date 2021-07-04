#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

template<typename T = std::chrono::milliseconds>
class Timer {
public:
    using clock = std::chrono::high_resolution_clock;

    Timer() : ostream_{std::cout} {}

    explicit Timer(std::ofstream& fileStream) : ostream_{fileStream} {}

    explicit Timer(const std::string& filepath) :
        fileStream_{filepath, std::ios::app},
        ostream_{fileStream_} {}

    ~Timer() {
        StopTimer();
    }

    Timer(const Timer& other) = delete;
    Timer& operator=(const Timer& other) = delete;

    Timer(Timer&& other) = delete;
    Timer& operator=(Timer&& other) = delete;

private:
    std::ofstream fileStream_{};
    std::ostream& ostream_;
    std::chrono::time_point<clock> startTimePoint_{clock::now()};

    void StopTimer() {
        const auto endTimePoint = clock::now();
        const auto start = std::chrono::time_point_cast<T>(startTimePoint_)
                               .time_since_epoch()
                               .count();
        const auto end = std::chrono::time_point_cast<T>(endTimePoint)
                             .time_since_epoch()
                             .count();
        SaveTime(start, end);
    }

    template<typename Count>
    void SaveTime(Count start, Count end);
};

template<>
template<typename Count>
void Timer<std::chrono::nanoseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << static_cast<double>(end - start) / 1000.0
             << " us  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::microseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << static_cast<double>(end - start) / 1000.0
             << " ms  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::milliseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << static_cast<double>(end - start) / 1000.0
             << " s  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::seconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << end - start << " s  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::minutes>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << end - start << " min  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::hours>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: " << end - start << " h  \n";
}

#endif // TIMER_HPP
