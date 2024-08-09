#pragma once

#include "CreatureNeuron.h"
#include "Creature.h"

#ifndef CREATURE_NEURON_GETROT_H
#define CREATURE_NEURON_GETROT_H

class NeuronGetRot : public CreatureNeuron {
public:
	NeuronGetRot(NeuronType type);	
	float CalcInputValue(Creature* creature) override;
};

#endif
