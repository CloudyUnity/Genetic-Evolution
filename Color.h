#pragma once
#include <cstdint>
#include <string>
#include <SDL.h>

#ifndef COLOR_H
#define COLOR_H

class Color {
public:
    Color(int r, int g, int b, int a);
    Color(int hex);
    Color();
    std::string ToString();
    uint32_t RGBAValue();
    void AddColor(Color color);
    SDL_Color ToSDLColor();

    static const Color BLACK;
    static const Color WHITE;
    static const Color RED;
    static const Color GREEN;
    static const Color BLUE;
    static const Color TRANS;
    static const Color PINK;
    static const Color PEACH;
    static const Color COZY_WHITE;
    static const Color LIGHT_BLUE;
    static const Color PURPLE;
    static const Color COZY_RED;
    static const Color CREAM;
    static const Color COZY_BLACK;

    int R = 0;
    int G = 0;
    int B = 0;
    int A = 0;
};

#endif 
