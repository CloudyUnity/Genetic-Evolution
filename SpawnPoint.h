#pragma once
#include "Vector2.h"

#ifndef SPAWN_POINT_H
#define SPAWN_POINT_H

class SpawnPoint {
public:
    static bool Active;
    static Vector2 Pos;

    static void Set(Vector2 pos);
};

#endif 
