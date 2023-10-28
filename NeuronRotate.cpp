#include "NeuronRotate.h"
#include "Creature.h"
#include "Logger.h"

NeuronRotate::NeuronRotate(NeuronType type) : CreatureNeuron(type) {}

void NeuronRotate::ApplyOutput(Creature* creature, float val) {
	creature->Rotate(val);
}