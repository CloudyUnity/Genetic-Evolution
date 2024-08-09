#include "NeuronON.h"
#include "UpdateManager.h"

NeuronON::NeuronON(NeuronType type) : CreatureNeuron(type) {}

float NeuronON::CalcInputValue(Creature* _) {
	return 1;
}