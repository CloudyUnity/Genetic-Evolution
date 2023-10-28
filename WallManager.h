#pragma once
#include "Shape.h"
#include <vector>

#ifndef WALL_MANAGER_H
#define WALL_MANAGER_H

class WallManager {
public:    
    static void AddShape(Shape* shape);
    static void RemoveShape(Shape* shape);
    
    static std::vector<Shape*> WallList;    
};

#endif 
