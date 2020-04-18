#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>

enum class Ostream : std::size_t { standard, file };

template<typename T = std::chrono::milliseconds>
class Timer {
public:
    explicit Timer(Ostream ostreamType = Ostream::standard,
                   std::string filepath = "") :
        ostreamType_{ostreamType},
        filepath_{std::move(filepath)},
        startTimePoint_{std::chrono::high_resolution_clock::now()} {}

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
    std::ostringstream ostream_{};
    Ostream ostreamType_{};
    std::string filepath_{};

    void StopTimer() {
        const auto endTimePoint = std::chrono::high_resolution_clock::now();
        const auto start = std::chrono::time_point_cast<T>(startTimePoint_)
                               .time_since_epoch()
                               .count();
        const auto end = std::chrono::time_point_cast<T>(endTimePoint)
                             .time_since_epoch()
                             .count();
        SaveTime(start, end);
        switch (ostreamType_) {
        case Ostream::standard:
            std::cout << ostream_.str();
            break;
        case Ostream::file:
            if (!filepath_.empty()) {
                std::ofstream file{filepath_};
                file << ostream_.str();
            }
            break;
        }
    }

    template<typename Count>
    void SaveTime(Count start, Count end);
};

template<>
template<typename Count>
void Timer<std::chrono::nanoseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: "
             << static_cast<double>(end - start) / 1000.0 << " us  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::microseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: "
             << static_cast<double>(end - start) / 1000.0 << " ms  \n";
}

template<>
template<typename Count>
void Timer<std::chrono::milliseconds>::SaveTime(Count start, Count end) {
    ostream_ << "Elapsed time: "
             << static_cast<double>(end - start) / 1000.0 << " s  \n";
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
