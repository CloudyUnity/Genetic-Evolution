#pragma once
#include <vector>
#include <string>

#ifndef CREATURE_GENOME_H
#define CREATURE_GENOME_H

class CreatureGenome {
public:
	CreatureGenome();
	CreatureGenome(std::vector<int> genes);

	std::vector<int> Genes;
	void InitRandomGenes(int genomeSize);
	std::string GetGenomeBinary();
	std::vector<int> Mutate(int mutations);
};

#endif
