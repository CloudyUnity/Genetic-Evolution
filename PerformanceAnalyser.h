#pragma once
#include <string>
#include <stack>
#include <chrono>

#ifndef PERFORMANCE_ANALYSER_H
#define PERFORMANCE_ANALYSER_H

class PerformanceAnalyser {
public:
    static std::stack<std::chrono::system_clock::time_point> Stack;

    static void PushTime();
    static long long PopTime(std::string label);
};

#endif // SHAPE_H
