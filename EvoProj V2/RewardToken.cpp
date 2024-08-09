#include "RewardToken.h"
#include "SimulationManager.h"

RewardToken::RewardToken(ShapeInfo info) : Collider(info, true, true) {
	SimulationManager::SubscribeToEventStartNewGen([this]() {
		CreaturesTouched.clear();
	});
}

void RewardToken::OnCreatureTrigger(Creature* creature) {
	if (std::find(CreaturesTouched.begin(), CreaturesTouched.end(), creature) != CreaturesTouched.end())
		return;

	if (SimulationSetup::REWARD_TOKEN_SPEED_BONUS)
		creature->RewardTokenCounter += 1 + (10 / UpdateManager::UpdatesSinceSimStart);
	else
		creature->RewardTokenCounter++;
	CreaturesTouched.push_back(creature);

	Info.Col = Color(rand() % 255, rand() % 255, rand() % 255, 255);
}