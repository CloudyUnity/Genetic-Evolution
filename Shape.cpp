#include "Shape.h"
#include "Logger.h" 
#include "PaintManager.h"
#include "SimulationSetup.h"
#include "WallManager.h"

Shape::Shape(ShapeInfo info)
{
    Info = info;
    Info.HalfScale = info.Scale.Mult(0.5);
    if (!info.ZoomDisabled)
        Parent = PaintManager::Scroller;

    if (info.Wall)
        WallManager::AddShape(this);

    PaintManager::AddShape(this);
}

Vector2 Shape::GetPointDirection() {
    double radians = Info.RotationAngle * (M_PI / 180.0);
    return Vector2(std::cos(radians), std::sin(radians));
}

void Shape::OnMouseClick() {
    Logger::AltLog("Error: Non-Clickable Shape has been clicked");
}

bool Shape::Contains(Vector2 point) {
    
    Vector2 pos = Info.Position;

    if (Info.ConnectedToEastWindowEdge)
        pos.X += SimulationSetup::WINDOW_BOUNDS.X;

    if (Info.ConnectedToSouthWindowEdge)
        pos.Y += SimulationSetup::WINDOW_BOUNDS.Y;

    Vector2 p1 = Vector2(-Info.HalfScale.X, -Info.HalfScale.Y);
    Vector2 p2 = Vector2(Info.HalfScale.X, -Info.HalfScale.Y);
    Vector2 p3 = Vector2(-Info.HalfScale.X, Info.HalfScale.Y);
    Vector2 p4 = Vector2(Info.HalfScale.X, Info.HalfScale.Y);

    double angle = Info.RotationAngle * (M_PI / 180.0);

    double rX = p1.X * cos(angle) - p1.Y * sin(angle);
    double rY = p1.X * sin(angle) + p1.Y * cos(angle);
    p1 = pos.Add(rX, rY);

    rX = p2.X * cos(angle) - p2.Y * sin(angle);
    rY = p2.X * sin(angle) + p2.Y * cos(angle);
    p2 = pos.Add(rX, rY);

    rX = p3.X * cos(angle) - p3.Y * sin(angle);
    rY = p3.X * sin(angle) + p3.Y * cos(angle);
    p3 = pos.Add(rX, rY);

    rX = p4.X * cos(angle) - p4.Y * sin(angle);
    rY = p4.X * sin(angle) + p4.Y * cos(angle);
    p4 = pos.Add(rX, rY);

    if ((p2.X - p1.X) * (point.Y - p1.Y) - (point.X - p1.X) * (p2.Y - p1.Y) <= 0)
        return false;
    if ((p4.X - p2.X) * (point.Y - p2.Y) - (point.X - p2.X) * (p4.Y - p2.Y) <= 0)
        return false;
    if ((p3.X - p4.X) * (point.Y - p4.Y) - (point.X - p4.X) * (p3.Y - p4.Y) <= 0)
        return false;
    if ((p1.X - p3.X) * (point.Y - p3.Y) - (point.X - p3.X) * (p1.Y - p3.Y) <= 0)
        return false;    

    return true;
}

void Shape::SetText(std::string txt) {
    Info.Text = txt;
    if (Info.CachedSurface)
        SDL_FreeSurface(Info.CachedSurface);
    if (Info.CachedTex)
        SDL_DestroyTexture(Info.CachedTex);

    Info.CachedSurface = nullptr;
    Info.CachedTex = nullptr;
}
