#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_AGE_H
#define CREATURE_NEURON_AGE_H

class NeuronAge : public CreatureNeuron{
public:
	NeuronAge(NeuronType type);
	float CalcInputValue(Creature* _) override;
};

#endif
