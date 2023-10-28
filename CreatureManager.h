#pragma once
#include <vector>
#include "Creature.h"
#include "PaintManager.h"

#ifndef CREATURE_MANAGER_H
#define CREATURE_MANAGER_H

class CreatureManager {
public:
	static std::vector<Creature*> CreatureList;
	static void AddToCreatureList(Creature* creature);

	static void SpawnCreatures(int amount);
	static void SpawnCreatures(std::vector<std::vector<int>> allGenes);
	static void Update();
	static void DeallocAll();

	static Creature* SelectedCreature;
	static void SetSelected(Creature* creature);
	static void DeselectSelected();
};

#endif
