#include "NeuronBorder.h"
#include "Creature.h"
#include "ArenaManager.h"

NeuronBorder::NeuronBorder(NeuronType type, bool vertical) : CreatureNeuron(type) {
	VerticalBorder = vertical;
}

float NeuronBorder::CalcInputValue(Creature* creature) {
	if (VerticalBorder) 
		return creature->Info.Position.Y / ArenaManager::ArenaSize.Y;
	
	return creature->Info.Position.X / ArenaManager::ArenaSize.X;
}