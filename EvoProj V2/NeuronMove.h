#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_MOVE_H
#define CREATURE_NEURON_MOVE_H

class NeuronMove : public CreatureNeuron {
public:
	NeuronMove(NeuronType type);
	void ApplyOutput(Creature* creature, float val) override;
};

#endif
