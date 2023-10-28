#include "WallManager.h"

std::vector<Shape*> WallManager::WallList;

void WallManager::AddShape(Shape* shape) {
	WallList.push_back(shape);
}

void WallManager::RemoveShape(Shape* shape) {
    auto it = std::remove(WallList.begin(), WallList.end(), shape);
    if (it != WallList.end()) {
        WallList.erase(it);
    }
}