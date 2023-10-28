#pragma once
#include <vector>
#include "CreatureNeuron.h"
#include "CreatureGenome.h"

#ifndef CREATURE_BRAIN_H
#define CREATURE_BRAIN_H

class CreatureBrain {
public:
	std::vector<CreatureNeuron*> InputNeurons;
	std::vector<CreatureNeuron*> InternalNeurons;
	std::vector<CreatureNeuron*> OutputNeurons;

	CreatureGenome Genome;

	void Init(int internalCount, std::vector<int> genes);
	void Init(int internalCount, int genomeSize);
	void DecodeGene(int gene);
	static std::vector<CreatureNeuron*> CreateInputNeurons();
	static std::vector<CreatureNeuron*> CreateOutputNeurons();
	void Update(Creature* creature);
	void EraseUselessNeurons();
};

#endif
