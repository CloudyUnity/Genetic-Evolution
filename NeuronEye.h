#pragma once

#include "CreatureNeuron.h"
#include "Vector2.h"
#include "UpdateManager.h"
#include "CreatureManager.h"
#include "SimulationSetup.h"

#ifndef CREATURE_NEURON_EYE_H
#define CREATURE_NEURON_EYE_H

class NeuronEye : public CreatureNeuron {
public:
	enum VisionType {
		CREATURE,
		WALL
	};
	VisionType Vision;
	Shape* RaycastLine;
	Vector2 Origin;
	double RotAngle;

	NeuronEye(NeuronType type, VisionType visionType, Vector2 origin, double rotAngle);
	float RayCastShape(Vector2 origin, Vector2 dir, Shape* shape);
	float CheckIntersection(Vector2 origin, Vector2 end, Vector2 p1, Vector2 p2);
	float CalcInputValue(Creature* creature) override;	
	void DeleteSelf() override;
};

#endif
