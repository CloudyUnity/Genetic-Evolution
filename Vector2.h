#pragma once
#include <string>

#ifndef VECTOR2_H
#define VECTOR2_H

class Vector2 {
public:
    Vector2(double x1, double y1);
    Vector2();
    Vector2 Mult(double multiplier);
    Vector2 Add(Vector2 other);
    Vector2 Add(double x1, double y1);
    Vector2 Add(double a);
    Vector2 Sub(Vector2 other);
    Vector2 Sub(double x1, double y1);
    float DotProduct(Vector2 other);
    Vector2 Clone();
    double Magnitude();
    Vector2 Normalized();
    Vector2 RoundToNearest(double rounder);

    std::string ToString();
    double X;
    double Y;

    static double Area(Vector2 A, Vector2 B, Vector2 C);
};

#endif // SHAPE_H
