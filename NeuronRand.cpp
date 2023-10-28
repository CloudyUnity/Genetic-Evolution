#include "NeuronRand.h"
#include "UpdateManager.h"
#include "SimulationSetup.h"
#include "Logger.h"

NeuronRand::NeuronRand(NeuronType type) : CreatureNeuron(type) {}

float NeuronRand::CalcInputValue(Creature* _) {
	return (rand() % 10000) / 10000.0;
}