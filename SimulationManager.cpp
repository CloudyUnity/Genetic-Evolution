#include "SimulationManager.h"
#include "Logger.h"
#include "HUDManager.h"

int SimulationManager::UpdatesPerFrame;
double SimulationManager::SimulationSecondsPerGen;
int SimulationManager::CreatureCount;
int SimulationManager::MutationAmount;
int SimulationManager::Generations;
int SimulationManager::InternalCount;
int SimulationManager::GeneCount;
std::vector<Creature*> SimulationManager::CurrentCreatures;

void SimulationManager::InitSim(int updates, double simSecs, int creatures, int internalCount, int geneCount) {
	UpdatesPerFrame = updates;
	SimulationSecondsPerGen	= simSecs;
	CreatureCount = creatures;
	InternalCount = internalCount;
	GeneCount = geneCount;

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
}

void SimulationManager::FilterCreatures() {

	CurrentCreatures = CreatureManager::CreatureList;

	for (int i = CurrentCreatures.size() - 1; i >= 0; i--) {
		if (!EvaluateCreature(CurrentCreatures.at(i)))
			CurrentCreatures.erase(CurrentCreatures.begin() + i);
	}
	if (CurrentCreatures.size() == 0)
		CurrentCreatures.push_back(CreatureManager::CreatureList.at(0));
}

bool SimulationManager::EvaluateCreature(Creature* creature) {
	return creature->Velocity.Magnitude() > 0.2f;
}

std::vector<std::vector<int>> SimulationManager::CollectGenInfo() {
	
	std::vector<std::vector<int>> AllGenomes;

	for (int i = 0; i < CreatureCount; i++) {
		int creatureIndex = i % CurrentCreatures.size();
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
}

void SimulationManager::ChangeSimSpeed(int updatesPerFrame) {
	UpdatesPerFrame = updatesPerFrame;
}

void SimulationManager::PauseSim() {
	ChangeSimSpeed(0);
}
