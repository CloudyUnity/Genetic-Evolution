#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_ROTATE_H
#define CREATURE_NEURON_ROTATE_H

class NeuronRotate : public CreatureNeuron {
public:
	NeuronRotate(NeuronType type);
	void ApplyOutput(Creature* creature, float val) override;
};

#endif
