#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_OSS_H
#define CREATURE_NEURON_OSS_H

class NeuronOscillator : public CreatureNeuron {
public:
	NeuronOscillator(NeuronType type);
	float CalcInputValue(Creature* _) override;
};

#endif
