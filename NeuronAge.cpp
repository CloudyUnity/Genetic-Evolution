#include "NeuronAge.h"
#include "UpdateManager.h"

NeuronAge::NeuronAge(NeuronType type) : CreatureNeuron(type) {}

float NeuronAge::CalcInputValue(Creature* _) {
	// Increases up to first 1M updates
	return UpdateManager::UpdatesSinceSimStart * 0.0001;
}