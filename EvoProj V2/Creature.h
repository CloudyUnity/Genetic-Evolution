#pragma once

#include "Shape.h"
#include "CreatureBrain.h"
#include "PaintManager.h"
#include "CreatureManager.h"
#include "SimulationSetup.h"
#include "BrainViewer.h"

#ifndef CREATURE_H
#define CREATURE_H

class Collider;

class Creature : public Shape {
public:
	Creature(ShapeInfo info, int inC, int gS);
	Creature(ShapeInfo info, int inC, std::vector<int> genes);

	void InitEyes();

	CreatureBrain Brain;
	Shape* eye1;
	Shape* eye2;

	Vector2 Velocity;
	int CollisionCounter;
	int RewardTokenCounter;

	void AddAccelerationForward(double amount);
	void Move();
	void Rotate(double amount);
	void Die();
	void Update();
	bool CheckCollision(Creature* other);
	bool CheckCollision(Collider* wall);

	void OnMouseClick() override;
};

#endif
