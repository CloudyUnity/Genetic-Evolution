#pragma once
#include <vector>
#include "CreatureManager.h"
#include "Creature.h"
#include "UpdateManager.h"

#ifndef SIMULATIONMAMAGER_H
#define SIMULATIONMAMAGER_H

class SimulationManager {
public:
    static int UpdatesPerFrame;
    static double SimulationSecondsPerGen;
    static int CreatureCount;
    static int MutationAmount;
    static int Generations;
    static int InternalCount;
    static int GeneCount;

    static std::vector<Creature*> CurrentCreatures;

    static void InitSim(int updatesPerFrame, double simSecs, int creatures, int intern, int gene); 
    static void Update();
    static void RestartSim();

    static void FilterCreatures(); 
    static bool EvaluateCreature(Creature* creature);

    static std::vector<std::vector<int>> CollectGenInfo(); 
    static void StartNextGen(); 

    static void ChangeSimSpeed(int updatesPerFrame);
    static void PauseSim();
};

#endif 
