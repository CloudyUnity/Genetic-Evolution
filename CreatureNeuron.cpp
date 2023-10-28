#include "CreatureNeuron.h"
#include "Logger.h"
#include <algorithm>

CreatureNeuron::CreatureNeuron(NeuronType type) {
	Type = type;
}

// Overriden by each unique input neuron
float CreatureNeuron::CalcInputValue(Creature* creature) {
	return 1;
}

void CreatureNeuron::AddConnection(CreatureNeuron* neuron, float weight) {
	Connection c = { neuron, weight };	
	Connections.push_back(c); // Program freezes
}

void CreatureNeuron::ApplyInput(float input) {
	AppliedInputs.push_back(input);
}

float CreatureNeuron::CalcOutputFromInputs() {

	float sumInputs = 0;
	for (int i = 0; i < AppliedInputs.size(); i++) {
		sumInputs += AppliedInputs.at(i);
	}

	AppliedInputs.clear();
	return (float)tanh(sumInputs);
}

void CreatureNeuron::Update(Creature* creature) {

	if (Type != NeuronType::OUTPUT && Connections.empty())
		return;

	float output = 0;
	if (Type == NeuronType::INPUT)
		output = CalcInputValue(creature);
	else
		output = CalcOutputFromInputs();	

	if (output == 0)
		return;

	output = std::clamp(output, -1.0f, 1.0f);

	if (Type == NeuronType::OUTPUT) {
		ApplyOutput(creature, output);
		return;
	}

	int size = Connections.size();
	for (int i = 0; i < size; i++) {
		Connection connection = Connections.at(i);
		connection.OutputNeuron->ApplyInput(output * connection.Weight);
	}
}

void CreatureNeuron::DeleteSelf() {	}

// Overriden by each unique output neuron
void CreatureNeuron::ApplyOutput(Creature* creature, float value) { }