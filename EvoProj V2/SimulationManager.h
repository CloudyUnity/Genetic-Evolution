#pragma once
#include <vector>
#include "CreatureManager.h"
#include "Creature.h"
#include "UpdateManager.h"
#include <functional>

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
    static double KnockOutPercent;

    static std::vector<Creature*> CurrentCreatures;

    static std::vector<std::function<void()>> EventOnStartNewGen;

    static void InitSim(int updatesPerFrame, double simSecs, int creatures, int intern, int gene, double knockOut, int mutationAmount); 
    static void Update();
    static void RestartSim();

    static void FilterCreatures(); 
    static bool EvaluateCreature(Creature* creature);
    static bool AGreaterThanB(const Creature* creatureA, const Creature* creatureB);

    static std::vector<std::vector<int>> CollectGenInfo(); 
    static void StartNextGen(); 

    static void ChangeSimSpeed(int updatesPerFrame);
    static void PauseSim();

    static void SubscribeToEventStartNewGen(std::function<void()> handler);
};

#endif 
