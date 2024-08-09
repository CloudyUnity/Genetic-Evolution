#pragma once
#include "Shape.h"
#include <functional>
#include "Creature.h"

#ifndef BUTTON_H
#define BUTTON_H

class Button : public Shape{
public:
    
    Button(ShapeInfo info, std::function<void()> func);

    std::function<void()> TriggerFunc;
    
    void OnMouseClick() override;
};

#endif 
