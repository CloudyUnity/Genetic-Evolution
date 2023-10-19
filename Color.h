#pragma once
#include <cstdint>
#include <string>

#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    Color(int r, int g, int b, int a);
    Color();
    std::string ToString();
    uint32_t RGBAValue();
    void AddColor(Color color);

    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0;
};

#endif 
