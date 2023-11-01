#pragma once

#include "CreatureNeuron.h"

#ifndef CREATURE_NEURON_BORDER_H
#define CREATURE_NEURON_BORDER_H

class NeuronBorder : public CreatureNeuron {
public:
	bool VerticalBorder = false;
	NeuronBorder(NeuronType type, bool vertical);
	float CalcInputValue(Creature* _) override;
};

#endif
