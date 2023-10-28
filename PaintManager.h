#pragma once
#include <wtypes.h>
#include "Shape.h"
#include <vector>
#include "SDL.h"
#include "SDL_ttf.h";

#ifndef PAINTMANAGER_H
#define PAINTMANAGER_H

class PaintManager {
public:
    static void Init();
    static void Draw();
    static void DrawShape(Shape* shape);
    static void DrawLine(Shape* shape);
    static void MoveScroller(Vector2 dir);
    static void AddShape(Shape* shape);
    static void RemoveShape(Shape* shape);
    static void CleanUp();
    static void DeallocAll();
    static void DrawTxt(Shape* shape, Vector2 pos, Vector2 scale);

    static SDL_Texture* LoadTexture(const char* imagePath);

    static std::vector<Shape*> ShapeList;
    static Shape* Scroller;
    static SDL_Window* Window;
    static SDL_Renderer* Rend;
    static SDL_Texture* Texture;
    static TTF_Font* MainFont;

    static double ZoomLevel;
};

#endif 
