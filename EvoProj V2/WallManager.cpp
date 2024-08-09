#include "WallManager.h"

std::vector<Collider*> WallManager::WallList;

void WallManager::AddShape(Collider* shape) {
	WallList.push_back(shape);
}

void WallManager::RemoveShape(Collider* shape) {
    auto it = std::remove(WallList.begin(), WallList.end(), shape);
    if (it != WallList.end()) {
        WallList.erase(it);
    }
}