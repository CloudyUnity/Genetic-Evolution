#include "Shape.h"
#include "Logger.h" 
#include "PaintManager.h"

Shape::Shape() {
    PaintManager::AddShape(this);
}

Shape::Shape(int posX, int posY, int scalX, int scalY) {
    Position = Vector2(posX, posY);
    Scale = Vector2(scalX, scalY);
    Text = "Default Shape";

    PaintManager::AddShape(this);
}
