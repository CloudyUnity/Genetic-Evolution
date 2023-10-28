#pragma once
#include "CreatureBrain.h"
#include "Shape.h"
#include <unordered_map>

#ifndef BRAIN_VIEWER_H
#define BRAIN_VIEWER_H

class BrainViewer {
public:
	static std::unordered_map<CreatureNeuron*, Shape*> NeuronShapeHashMap;
	static std::vector<Shape*> CurrentShapes;

	static void DisplayBrain(CreatureBrain brain);
	static void ConvertToNeuronShapes(std::vector<CreatureNeuron*> list);
	static void ClearOldBrain();
};

#endif
