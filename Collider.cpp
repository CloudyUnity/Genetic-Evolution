#include "Collider.h"
#include "WallManager.h"

Collider::Collider(ShapeInfo info, bool trigger, bool enabled) : Shape(info) {
	Trigger = trigger;
	Enabled = enabled;
	WallManager::AddShape(this);
}

void Collider::OnCreatureTrigger(Creature* creature)
{
}
