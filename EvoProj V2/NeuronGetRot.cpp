#include "NeuronGetRot.h"

NeuronGetRot::NeuronGetRot(NeuronType type) : CreatureNeuron(type) {}

float NeuronGetRot::CalcInputValue(Creature* creature) {
	int rem = (int)creature->Info.RotationAngle % 360;
	return rem / 360.0;
}