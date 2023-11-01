#pragma once
#include "Collider.h"

#ifndef REWARD_TOKEN_H
#define REWARD_TOKEN_H

class RewardToken : public Collider {
public:
    RewardToken(ShapeInfo info);
    std::vector<Creature*> CreaturesTouched;

    void OnCreatureTrigger(Creature* creature) override;
};

#endif
