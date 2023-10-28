#pragma once
#include "Vector2.h"
#include "Color.h"

#ifndef SHAPE_H
#define SHAPE_H

class Shape {
public:
    struct ShapeInfo {
        int Layer = 0;        

        // Rendering
        Vector2 Position;
        Vector2 Scale;
        Vector2 HalfScale;
        double RotationAngle = 0;
        int BorderSize = 0;
        bool ConnectedToEastWindowEdge = false;
        bool ConnectedToSouthWindowEdge = false;
        bool ZoomDisabled = false;
        bool QuickDrawDisabled = false;

        // Coloring
        Color Col;
        Color BorderColor;

        // Text
        bool RenderText = false;
        std::string Text = "Default Shape";
        Color TextColor;
        SDL_Texture* CachedTex = nullptr;
        SDL_Surface* CachedSurface = nullptr;

        // Properties        
        bool Filled = true;
        bool Visible = true;
        bool Wall = false;

        // Interactivity
        bool Hoverable = false;
        bool Clickable = false;

        // Line
        bool IsLine = false;
        Vector2 LineEndPosition;

        // Unused
        bool IsCircle = false;
    };

    Shape(ShapeInfo info);

    Vector2 GetPointDirection();
    bool Contains(Vector2 point);
    void SetText(std::string txt);

    virtual void OnMouseClick();
    Shape* Parent = nullptr;

    ShapeInfo Info;    
};

#endif
