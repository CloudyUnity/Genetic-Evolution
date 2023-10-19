#pragma once
#include <string>

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    Vector2(double x1, double y1);
    Vector2();
    std::string ToString();
    double X;
    double Y;
};

#endif // SHAPE_H
