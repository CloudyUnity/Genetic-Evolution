#include "CreatureGenome.h"
#include <cstdlib>
#include "math.h"
#include <random>
#include <SDL.h>

CreatureGenome::CreatureGenome() {}
CreatureGenome::CreatureGenome(std::vector<int> genes) {
	Genes = genes;
}

void CreatureGenome::InitRandomGenes(int genomeSize) {
	Genes.resize(genomeSize);

	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<uint32_t> uint_dist;

	for (int i = 0; i < Genes.size(); i++) {
		Genes.at(i) = uint_dist(mt);
	}
}

std::string CreatureGenome::GetGenomeBinary() {
	std::string string = "";
	int mask = 0b10000000000000000000000000000000;

	for (int i = 0; i < Genes.size(); i++) {

		int number = Genes.at(i);

		bool negative = number < 0;
		if (negative)
			number ^= mask;					

		std::string result;
		for (int bit = 0; bit < 32; bit++) {

			if (number <= 0) {
				result = "0" + result;
				continue;
			}

			result = (number % 2 == 0 ? "0" : "1") + result;
			number /= 2;
		}

		if (negative)
			result[0] = '1';

		result.insert(1, " "); // 0 0000000 0 0000000 0000000000000000
		result.insert(9, " ");
		result.insert(11, " ");
		result.insert(19, " ");

		string += std::to_string(Genes.at(i)) + " - " + result + "\n";
	}

	return string;
}

std::vector<int> CreatureGenome::Mutate(int mutations) {

	std::vector<int> genes = Genes;

	for (int i = 0; i < mutations; i++) {
		int randGene = rand() % genes.size();
		int gene = genes.at(randGene);

		int randBit = rand() % 32;
		int mask = 1 << randBit;
		gene ^= mask;

		genes.at(randGene) = gene;
	}

	return genes;
}