#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_RAND_H
#define CREATURE_NEURON_RAND_H

class NeuronRand : public CreatureNeuron {
public:
	NeuronRand(NeuronType type);
	float CalcInputValue(Creature* _) override;
};

#endif
