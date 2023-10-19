#pragma once
#include <wtypes.h>
#include "Shape.h"
#include <vector>
#include "SDL.h"

#ifndef PAINTMANAGER_H
#define PAINTMANAGER_H

class PaintManager {
public:
    static void Init();
    static void Draw();
    static void DrawShape(Shape* shape);
    static void AddShape(Shape* shape);
    static void CleanUp();
    static std::vector<Shape*> ShapeList;
    static SDL_Window* Window;
    static SDL_Renderer* Rend;
};

#endif 
