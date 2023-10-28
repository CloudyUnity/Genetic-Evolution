#include "NeuronOscillator.h"
#include "UpdateManager.h"
#include "SimulationSetup.h"

NeuronOscillator::NeuronOscillator(NeuronType type) : CreatureNeuron(type) {}

float NeuronOscillator::CalcInputValue(Creature* _) {
	return 0.5 * sin(SimulationSetup::CREATURE_OSS_PERIOD * UpdateManager::UpdatesSinceSimStart) + 0.5;
}