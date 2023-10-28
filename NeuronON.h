#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_ON_H
#define CREATURE_NEURON_ON_H

class NeuronON : public CreatureNeuron {
public:
	NeuronON(NeuronType type);
	float CalcInputValue(Creature* _) override;
};

#endif
