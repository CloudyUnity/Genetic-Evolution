#include "NeuronAge.h"
#include "UpdateManager.h"
#include "SimulationManager.h"

NeuronAge::NeuronAge(NeuronType type) : CreatureNeuron(type) {}

float NeuronAge::CalcInputValue(Creature* _) {
	return UpdateManager::UpdatesSinceSimStart / (SimulationManager::SimulationSecondsPerGen * 100);
}