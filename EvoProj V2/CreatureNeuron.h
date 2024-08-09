#pragma once

#include <vector>

// Forward declaration to avoid circular dependencies
class Creature;

#ifndef CREATURE_NEURON_H
#define CREATURE_NEURON_H

class CreatureNeuron {
public:

	struct Connection {
		CreatureNeuron* OutputNeuron;
		float Weight;
	};

	std::vector<Connection> Connections;
	std::vector<float> AppliedInputs;

	enum NeuronType {
		INPUT,
		INTERNAL,
		OUTPUT
	};

	NeuronType Type;

	CreatureNeuron(NeuronType type);
	virtual float CalcInputValue(Creature* creature);
	virtual void ApplyOutput(Creature* creature, float val);
	virtual void DeleteSelf();
	void ApplyInput(float input);
	float CalcOutputFromInputs();
	void Update(Creature* creature);
	void AddConnection(CreatureNeuron* neuron, float weight);
};

#endif
