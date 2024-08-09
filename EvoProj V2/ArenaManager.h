#pragma once
#include "Vector2.h"
#include "SimulationSetup.h"
#include "RewardToken.h"

#ifndef ARENA_MANAGER_H
#define ARENA_MANAGER_H

class ArenaManager {
public:
	static bool WrapAround;
	static Vector2 ArenaSize;
	static Vector2 MaxBounds;
	static Vector2 MinBounds;
	static Color ArenaColor;	

	static void Init(Vector2 size, bool wrapAround, int wrapPadding, Color color, bool wallsEnabled);
	static void MakeArenaShapes();
	static void MakeWalls();
	static void MakeTokens();
};

#endif
