#include "NeuronMove.h"
#include "Creature.h"
#include "Logger.h"

NeuronMove::NeuronMove(NeuronType type) : CreatureNeuron(type) {}

void NeuronMove::ApplyOutput(Creature* creature, float val) {
	//Logger::Log("Moving forward! " + std::to_string(val));
	creature->AddAccelerationForward(val);
}