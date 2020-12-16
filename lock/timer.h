#pragma once

#include <chrono>
#include <iostream>

class timer{
public:
    timer() {
        length_ = std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count();
    }

    ~timer() {
        std::cout << std::chrono::time_point_cast<std::chrono::microseconds>(std::chrono::system_clock::now()).time_since_epoch().count() - length_ << std::endl;
    }

private:
    int64_t length_;
};
