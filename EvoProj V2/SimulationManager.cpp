#include "SimulationManager.h"
#include "Logger.h"
#include "HUDManager.h"
#include <algorithm>

int SimulationManager::UpdatesPerFrame;
double SimulationManager::SimulationSecondsPerGen;
double SimulationManager::KnockOutPercent;
int SimulationManager::CreatureCount;
int SimulationManager::MutationAmount;
int SimulationManager::Generations;
int SimulationManager::InternalCount;
int SimulationManager::GeneCount;
std::vector<Creature*> SimulationManager::CurrentCreatures;
std::vector<std::function<void()>> SimulationManager::EventOnStartNewGen;

// =============================== SIMULATION EVALUATION AND SORTING =============================================
// Removes all creatures which don't pass this function
bool SimulationManager::EvaluateCreature(Creature* creature) {
	return true;
}

// Sorts the list from highest to lowest rewards based on this function
bool SimulationManager::AGreaterThanB(const Creature* creatureA, const Creature* creatureB) {
	return creatureA->RewardTokenCounter > creatureB->RewardTokenCounter;
}
// =============================== SIMULATION EVALUATION AND SORTING =============================================

void SimulationManager::InitSim(int updates, double simSecs, int creatures, int internalCount, int geneCount, double knockOut, int mutationAmount) {
	UpdatesPerFrame = updates;
	SimulationSecondsPerGen	= simSecs;
	CreatureCount = creatures;
	InternalCount = internalCount;
	GeneCount = geneCount;
	KnockOutPercent = knockOut;
	MutationAmount = mutationAmount;

	HUDManager::CreatureCountTXT->SetText(std::to_string(CreatureCount) + " Creatures");
	HUDManager::GenesTXT->SetText(std::to_string(GeneCount) + " Genes");
	HUDManager::InternalsTXT->SetText(std::to_string(InternalCount) + " Brain Size");
	HUDManager::GenTXT->SetText("Generation #" + std::to_string(Generations));

	CreatureManager::SpawnCreatures(CreatureCount);
}

void SimulationManager::Update() {

	if (UpdateManager::UpdatesSinceSimStart == SimulationSecondsPerGen * 100) {
		StartNextGen();
		UpdateManager::UpdatesSinceSimStart = 0;
		Generations++;
		BrainViewer::ClearOldBrain();
		CreatureManager::DeselectSelected();
		HUDManager::GenTXT->SetText("Generation #" + std::to_string(Generations));
	}
}

void SimulationManager::RestartSim() {
	CreatureManager::DeallocAll();
	CreatureManager::SpawnCreatures(CreatureCount);
	Generations = 0;
	UpdateManager::UpdatesSinceSimStart = 0;
	BrainViewer::ClearOldBrain();
	CreatureManager::DeselectSelected();
	HUDManager::GenTXT->SetText("Generation #" + std::to_string(Generations));

	for (const auto& handler : EventOnStartNewGen) {
		handler();
	}
}

void SimulationManager::FilterCreatures() {

	CurrentCreatures = CreatureManager::CreatureList;

	for (int i = CurrentCreatures.size() - 1; i >= 0; i--) {
		if (!EvaluateCreature(CurrentCreatures.at(i)))
			CurrentCreatures.erase(CurrentCreatures.begin() + i);
	}
	if (CurrentCreatures.size() == 0)
		CurrentCreatures.push_back(CreatureManager::CreatureList.at(0));

	std::sort(CurrentCreatures.begin(), CurrentCreatures.end(), AGreaterThanB);	

	int cutOffIndex = (int)(CurrentCreatures.size() * KnockOutPercent);
	CurrentCreatures.erase(CurrentCreatures.begin() + cutOffIndex, CurrentCreatures.end());
}

std::vector<std::vector<int>> SimulationManager::CollectGenInfo() {
	
	std::vector<std::vector<int>> AllGenomes;

	for (int i = SimulationSetup::NO_MUTATION_BEST_OF_COUNT - 1; i >= 0; i--) {
		AllGenomes.push_back(CurrentCreatures.at(i)->Brain.Genome.Genes);
	}

	for (int i = 0; AllGenomes.size() < CreatureCount; i++) {
		int creatureIndex = i % CurrentCreatures.size();

		double chance = 1.0 / (creatureIndex + 10.0);
		double randVal = static_cast<double>(rand()) / RAND_MAX;

		if (randVal < chance)
			AllGenomes.push_back(CurrentCreatures.at(creatureIndex)->Brain.Genome.Mutate(MutationAmount));
	}

	return AllGenomes;
}

void SimulationManager::StartNextGen() {
	
	FilterCreatures();
	std::vector<std::vector<int>> genes = CollectGenInfo();

	std::string geneDataLog;
	for (int i = 0; i < genes.size(); i++)
		for (int j = 0; j < genes.at(i).size(); j++)
			geneDataLog += std::to_string(i) + " , " + std::to_string(genes.at(i).at(j)) + "\n";
	Logger::HardLog(geneDataLog, "LastGeneData");

	CreatureManager::DeallocAll();
	CreatureManager::SpawnCreatures(genes);

	for (const auto& handler : EventOnStartNewGen) {
		handler();
	}
}

void SimulationManager::ChangeSimSpeed(int updatesPerFrame) {
	UpdatesPerFrame = updatesPerFrame;
}

void SimulationManager::PauseSim() {
	ChangeSimSpeed(0);
}

void SimulationManager::SubscribeToEventStartNewGen(std::function<void()> handler) {
	EventOnStartNewGen.push_back(handler);
}
