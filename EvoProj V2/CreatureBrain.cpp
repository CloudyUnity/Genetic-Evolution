#include "CreatureBrain.h"
#include "Logger.h"
#include "NeuronAge.h"
#include "NeuronON.h"
#include "NeuronMove.h"
#include "NeuronRotate.h"
#include "NeuronEye.h"
#include "NeuronOscillator.h"
#include "NeuronRand.h"
#include "NeuronGetRot.h"
#include "NeuronBorder.h"

void CreatureBrain::Init(int internalCount, int genomeSize) {
	InputNeurons = CreateInputNeurons();	
	OutputNeurons = CreateOutputNeurons();

	for (int i = 0; i < internalCount; i++) {
		CreatureNeuron* neuron = new CreatureNeuron(CreatureNeuron::NeuronType::INTERNAL);
		InternalNeurons.push_back(neuron);
	}		

	Genome.InitRandomGenes(genomeSize);

	//Logger::Log(Genome.GetGenomeBinary());

	for (int geneI = 0; geneI < Genome.Genes.size(); geneI++)
		DecodeGene(Genome.Genes.at(geneI));

	EraseUselessNeurons();
	EraseUselessNeurons();
}

void CreatureBrain::Init(int internalCount, std::vector<int> genes) {
	InputNeurons = CreateInputNeurons();
	OutputNeurons = CreateOutputNeurons();

	for (int i = 0; i < internalCount; i++) {
		CreatureNeuron* neuron = new CreatureNeuron(CreatureNeuron::NeuronType::INTERNAL);
		InternalNeurons.push_back(neuron);
	}

	Genome.Genes = genes;

	for (int geneI = 0; geneI < Genome.Genes.size(); geneI++)
		DecodeGene(Genome.Genes.at(geneI));

	EraseUselessNeurons();
	EraseUselessNeurons();
}

void CreatureBrain::DecodeGene(int gene) {
	
	int internalSize = InternalNeurons.size();

	bool inputSource = (gene & 0b10000000000000000000000000000000) != 0 || internalSize == 0;

	int sourceID = (gene & 0b01111111000000000000000000000000) >> 24;
	sourceID %= inputSource ? InputNeurons.size() : internalSize;

	bool outputSink = (gene & 0b00000000100000000000000000000000) != 0 || internalSize == 0;

	int sinkID = (gene & 0b000000000011111110000000000000000) >> 16;
	sinkID %= outputSink ? OutputNeurons.size() : internalSize;

	float connectionWeight = (float)(gene & 0b00000000000000001111111111111111);
	connectionWeight /= 65536;
	connectionWeight -= 0.5f;
	connectionWeight *= 8;

	/*Logger::Log(std::to_string(gene) + " " + std::to_string(inputSource) + " " + std::to_string(sourceID) +
			" " + std::to_string(outputSink) + " " + std::to_string(sinkID) + " " + std::to_string(connectionWeight));*/

	CreatureNeuron* source = inputSource ? InputNeurons.at(sourceID) : InternalNeurons.at(sourceID);
	CreatureNeuron* sink = outputSink ? OutputNeurons.at(sinkID) : InternalNeurons.at(sinkID);
	source->AddConnection(sink, connectionWeight);
}

std::vector<CreatureNeuron*> CreatureBrain::CreateInputNeurons() {
	std::vector<CreatureNeuron*> neurons;

	CreatureNeuron* neuron = new NeuronAge(CreatureNeuron::NeuronType::INPUT);
	neurons.push_back(neuron);

	neuron = new NeuronON(CreatureNeuron::NeuronType::INPUT);
	neurons.push_back(neuron);

	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::CREATURE, Vector2(10, 0), 0);
	neurons.push_back(neuron);
	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::CREATURE, Vector2(10, 3), 45);
	neurons.push_back(neuron);
	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::CREATURE, Vector2(10, -3), -45);
	neurons.push_back(neuron);

	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::WALL, Vector2(10, 0), 0);
	neurons.push_back(neuron);
	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::WALL, Vector2(10, 3), 45);
	neurons.push_back(neuron);
	neuron = new NeuronEye(CreatureNeuron::NeuronType::INPUT, NeuronEye::VisionType::WALL, Vector2(10, -3), -45);
	neurons.push_back(neuron);

	neuron = new NeuronOscillator(CreatureNeuron::NeuronType::INPUT);
	neurons.push_back(neuron);

	neuron = new NeuronRand(CreatureNeuron::NeuronType::INPUT);
	neurons.push_back(neuron);

	neuron = new NeuronGetRot(CreatureNeuron::NeuronType::INPUT);
	neurons.push_back(neuron);

	neuron = new NeuronBorder(CreatureNeuron::NeuronType::INPUT, false);
	neurons.push_back(neuron);

	neuron = new NeuronBorder(CreatureNeuron::NeuronType::INPUT, true);
	neurons.push_back(neuron);
	
	return neurons;
}

std::vector<CreatureNeuron*> CreatureBrain::CreateOutputNeurons() {
	std::vector<CreatureNeuron*> neurons;

	CreatureNeuron* neuron = new NeuronMove(CreatureNeuron::NeuronType::OUTPUT);
	neurons.push_back(neuron);
	neuron = new NeuronRotate(CreatureNeuron::NeuronType::OUTPUT);
	neurons.push_back(neuron);

	return neurons;
}

void CreatureBrain::EraseUselessNeurons() {

	std::vector<CreatureNeuron*> connectedOutputs;
	std::vector<CreatureNeuron*> connectedInternals;

	for (int i = InternalNeurons.size() - 1; i >= 0; i--) {
		if (InternalNeurons.at(i)->Connections.empty()) {
			InternalNeurons.at(i)->DeleteSelf();
			InternalNeurons.erase(InternalNeurons.begin() + i);
			continue;
		}

		bool hasUsefulConnection = false;
		for (int c = 0; c < InternalNeurons.at(i)->Connections.size(); c++) {
			CreatureNeuron* output = InternalNeurons.at(i)->Connections.at(c).OutputNeuron;

			if (output->Type == CreatureNeuron::NeuronType::OUTPUT) {
				hasUsefulConnection = true;
				connectedOutputs.push_back(output);
				continue;
			}

			if (output->Type == CreatureNeuron::NeuronType::INTERNAL && output != InternalNeurons.at(i)) {
				hasUsefulConnection = true;
				connectedInternals.push_back(output);
			}
		}

		if (!hasUsefulConnection) {
			InternalNeurons.at(i)->DeleteSelf();
			InternalNeurons.erase(InternalNeurons.begin() + i);
		}			
	}

	for (int i = InputNeurons.size() - 1; i >= 0; i--) {
		if (InputNeurons.at(i)->Connections.empty()) {
			InputNeurons.at(i)->DeleteSelf();
			InputNeurons.erase(InputNeurons.begin() + i);
			continue;
		}

		bool hasUsefulConnection = false;
		for (int c = 0; c < InputNeurons.at(i)->Connections.size(); c++) {
			CreatureNeuron* output = InputNeurons.at(i)->Connections.at(c).OutputNeuron;

			if (output->Type == CreatureNeuron::NeuronType::OUTPUT) {
				hasUsefulConnection = true;
				connectedOutputs.push_back(output);
				continue;
			}

			if (output->Type == CreatureNeuron::NeuronType::INTERNAL && !output->Connections.empty()) {
				hasUsefulConnection = true;
				connectedInternals.push_back(output);
			}
		}

		if (!hasUsefulConnection) {
			InputNeurons.at(i)->DeleteSelf();
			InputNeurons.erase(InputNeurons.begin() + i);
		}			
	}

	for (int i = InternalNeurons.size() - 1; i >= 0; i--) {

		if (std::find(connectedInternals.begin(), connectedInternals.end(), InternalNeurons.at(i)) == connectedInternals.end()) {
			InternalNeurons.at(i)->DeleteSelf();
			InternalNeurons.erase(InternalNeurons.begin() + i);
		}
	}

	for (int i = OutputNeurons.size() - 1; i >= 0; i--) {
		
		if (std::find(connectedOutputs.begin(), connectedOutputs.end(), OutputNeurons.at(i)) == connectedOutputs.end()) {
			OutputNeurons.at(i)->DeleteSelf();
			OutputNeurons.erase(OutputNeurons.begin() + i);
		}
	}
}

void CreatureBrain::Update(Creature* creature) {

	int size = InputNeurons.size();
	for (int i = 0; i < size; i++) {
		InputNeurons.at(i)->Update(creature);
	}
	size = InternalNeurons.size();
	for (int i = 0; i < size; i++) {
		InternalNeurons.at(i)->Update(creature);
	}
	size = OutputNeurons.size();
	for (int i = 0; i < size; i++) {
		OutputNeurons.at(i)->Update(creature);
	}
}