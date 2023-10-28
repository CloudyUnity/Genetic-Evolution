#include "CreatureManager.h"
#include "PerformanceAnalyser.h"
#include "SimulationSetup.h"
#include "Logger.h"
#include "SimulationManager.h"
#include "SpawnPoint.h"
#include "WallManager.h"

std::vector<Creature*> CreatureManager::CreatureList;
Creature* CreatureManager::SelectedCreature;

void CreatureManager::SpawnCreatures(int amount) {

	for (int i = 0; i < amount; i++) {

		Shape::ShapeInfo info;
		Vector2 max = SimulationSetup::MAX_BOUNDS;
		Vector2 min = SimulationSetup::MIN_BOUNDS;
		info.Position = SpawnPoint::Active ? SpawnPoint::Pos : Vector2(rand() % (int)max.X + min.X, rand() % (int)max.Y + min.Y);		
		info.Scale = Vector2(20, 10);
		info.Col = SimulationSetup::CREATURE_COLOR;
		info.BorderColor = SimulationSetup::CREATURE_BORDER_COLOR;
		info.BorderSize = 2;
		info.Text = "Creature";
		info.RotationAngle = rand() % 360;
		info.Clickable = true;
		info.Hoverable = true;
		Creature* creature = new Creature(info, SimulationManager::InternalCount, SimulationManager::GeneCount);
	}
}

void CreatureManager::SpawnCreatures(std::vector<std::vector<int>> allGenes) {

	for (int i = 0; i < allGenes.size(); i++) {

		Shape::ShapeInfo info;
		Vector2 max = SimulationSetup::MAX_BOUNDS;
		Vector2 min = SimulationSetup::MIN_BOUNDS;
		info.Position = SpawnPoint::Active ? SpawnPoint::Pos : Vector2(rand() % (int)max.X + min.X, rand() % (int)max.Y + min.Y);
		info.Scale = Vector2(20, 10);
		info.Col = SimulationSetup::CREATURE_COLOR;
		info.BorderColor = SimulationSetup::CREATURE_BORDER_COLOR;
		info.BorderSize = 2;
		info.Text = "Creature";
		info.RotationAngle = rand() % 360;
		info.Clickable = true;
		info.Hoverable = true;
		Creature* creature = new Creature(info, SimulationManager::InternalCount, allGenes.at(i));
	}
}

void CreatureManager::AddToCreatureList(Creature* creature) {
	CreatureList.push_back(creature);
}

void CreatureManager::Update() {

	PerformanceAnalyser::PushTime();
	for (int i = 0; i < CreatureList.size(); i++) {
		CreatureList.at(i)->Update();
	}
	PerformanceAnalyser::PopTime("Creature Update()");

	if (!SimulationSetup::CREATURE_COLLISION_ON)
		return;

	std::vector<Creature*> CreatureCollisionCheckList = CreatureList;

	PerformanceAnalyser::PushTime();
	int wallListSize = WallManager::WallList.size();
	for (int i = CreatureCollisionCheckList.size() - 1; i >= 0; i--) {
		Creature* creatureA = CreatureCollisionCheckList.at(i);

		for (int w = 0; w < wallListSize; w++) {
			creatureA->CheckCollision(WallManager::WallList.at(w));
		}

		bool anyCollision = false;
		for (int j = i - 1; j >= 0; j--) {
			Creature* creatureB = CreatureCollisionCheckList.at(j);
			bool collision = creatureA->CheckCollision(creatureB);
			if (collision)
				anyCollision = true;
		}
		if (!anyCollision)
			CreatureCollisionCheckList.erase(CreatureCollisionCheckList.begin() + i);
	}
	PerformanceAnalyser::PopTime("Creature physics");
}

void CreatureManager::DeallocAll() {

	for (int c = CreatureList.size() - 1; c >= 0; c--) {
		
		Creature* creature = CreatureList.at(c);
		for (int n = creature->Brain.InputNeurons.size() - 1; n >= 0; n--) {
			creature->Brain.InputNeurons.at(n)->DeleteSelf();
			delete creature->Brain.InputNeurons.at(n);
		}
		for (int n = creature->Brain.InternalNeurons.size() - 1; n >= 0; n--) {
			creature->Brain.InternalNeurons.at(n)->DeleteSelf();
			delete creature->Brain.InternalNeurons.at(n);
		}
		for (int n = creature->Brain.OutputNeurons.size() - 1; n >= 0; n--) {
			creature->Brain.OutputNeurons.at(n)->DeleteSelf();
			delete creature->Brain.OutputNeurons.at(n);
		}

		PaintManager::RemoveShape(creature->eye1);
		PaintManager::RemoveShape(creature->eye2);
		PaintManager::RemoveShape(creature);
	}
	CreatureList.clear();
}

void CreatureManager::SetSelected(Creature* creature) {
	if (creature == nullptr)
		return;

	creature->Info.Col = SimulationSetup::CREATURE_SELECTED_COLOR;
	SelectedCreature = creature;
}

void CreatureManager::DeselectSelected() {
	if (SelectedCreature == nullptr)
		return;

	SelectedCreature->Info.Col = SimulationSetup::CREATURE_COLOR;
	SelectedCreature = nullptr;
}