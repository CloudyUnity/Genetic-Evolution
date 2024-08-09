// EvoProj V2.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "Shape.h"
#include "Logger.h"
#include "UpdateManager.h"
#include "PaintManager.h"
#include <iostream>
#include "CreatureGenome.h"
#include "Creature.h"
#include "CreatureManager.h"
#include "SimulationSetup.h"
#include "InputManager.h"
#include "HUDManager.h"
#include "SimulationManager.h"
#include "SpawnPoint.h"
#include "ArenaManager.h"

int main(int argc, char* argv[])
{   
    unsigned int seed = (int)time(0);
    srand(seed);

    Logger::Init();
    Logger::Log("Logger Init Done");

    PaintManager::Init();
    Logger::Log("Paint Init Done");

    InputManager::Init();
    Logger::Log("Input Init Done");

    HUDManager::Init();
    Logger::Log("HUD Init Done");

    SpawnPoint::Set(Vector2(300, 300));
    ArenaManager::Init(Vector2(3000, 1500), false, 20, Color::COZY_WHITE, true);
    SimulationManager::InitSim(1, 13, 150,10, 35, 0.5, 6);

    Logger::Log("Initialisation complete, starting update loop");    

    UpdateManager::BeginUpdateLoop();

    Logger::Log("Beginning deallocation");
    PaintManager::CleanUp();

    Logger::Log("Program ended successfully, closing Logger");
    Logger::CloseStream();

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
