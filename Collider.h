#pragma once
#include "Shape.h"
#include "Creature.h"

#ifndef COLLIDER_H
#define COLLIDER_H

class Collider : public Shape {
public:
    bool Trigger;
    bool Enabled;

    Collider(ShapeInfo info, bool trigger, bool enabled);
    virtual void OnCreatureTrigger(Creature* creature);
};

#endif
