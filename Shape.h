#pragma once
#include "Vector2.h"
#include "Color.h"


#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    Shape();
    Shape(int posX, int posY, int scalX, int scalY);

    int Layer = 0;
    Vector2 Position;
    Vector2 Scale;

    int BorderSize = 0;
    Color Col = Color();
    bool Filled = true;
    bool Visible = true;

    std::string Text = "";
};

#endif // SHAPE_H
