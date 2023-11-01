#pragma once
#include "Collider.h"
#include <vector>

#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

class WallManager {
public:    
    static void AddShape(Collider* shape);
    static void RemoveShape(Collider* shape);
    
    static std::vector<Collider*> WallList;
};

#endif 
