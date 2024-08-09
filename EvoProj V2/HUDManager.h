#pragma once
#include "SimulationSetup.h"
#include "Shape.h"
#include "Button.h"
#include "Logger.h"
#include "SimulationManager.h"

#ifndef HUD_MANAGER_H
#define HUD_MANAGER_H

class HUDManager {
public:
	static Shape* GenTXT;
	static Shape* FPSTXT;
	static Shape* CreatureCountTXT;
	static Shape* GenesTXT;
	static Shape* InternalsTXT;
	static Shape* GenProgressTXT;

	static Button* PauseBttn;

	static void Init();
	static void PauseSim();
	static void FastForward();
	static void Update();
};

#endif
