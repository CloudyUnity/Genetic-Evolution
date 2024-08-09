#include "UpdateManager.h"
#include <chrono>
#include <thread>
#include "Logger.h"
#include "Shape.h"
#include "Windows.h"
#include "PaintManager.h"
#include "SDL.h"
#include "Creature.h"
#include "CreatureManager.h"
#include "BrainViewer.h"
#include "PerformanceAnalyser.h"
#include <algorithm>
#include "SimulationSetup.h"
#include "InputManager.h"
#include "SimulationManager.h"
#include "HUDManager.h"

bool UpdateManager::Running;
int UpdateManager::UpdatesSinceSimStart;
double UpdateManager::FPS;
std::deque<double> UpdateManager::LastFrameDurations;

void UpdateManager::BeginUpdateLoop() {

	Running = true;

	const int SECONDS_TO_RUN = 15;
	int loops = SECONDS_TO_RUN * 1000 / SimulationSetup::UPDATE_SPEED;

	if (!SimulationSetup::LIMITED_PROGRAM_TIME)
		loops = 99999999999;	

	for (int i = 0; i < loops && Running; i++) {

		PerformanceAnalyser::PushTime();
		Logger::Log("\nUpdate #" + std::to_string(UpdatesSinceSimStart));

		for (int j = 0; j < SimulationManager::UpdatesPerFrame; j++) {			
			UpdateManager::Update();			
			UpdatesSinceSimStart++;
		}		

		SDLUpdate();
		HUDManager::Update();

		PerformanceAnalyser::PushTime();
		PaintManager::Draw();
		PerformanceAnalyser::PopTime("Render update time");

		int duration = (int)PerformanceAnalyser::PopTime("Update loop");
		LastFrameDurations.push_back(duration);
		if (LastFrameDurations.size() > SimulationSetup::FRAMERATE_FRAME_COUNT)
			LastFrameDurations.pop_front();

		double average = 0;
		for (const double& duration : LastFrameDurations) {
			average += duration;
		}
		average /= LastFrameDurations.size();
		FPS = round(1000 / (average));

		int timeError = std::clamp(SimulationSetup::UPDATE_SPEED - duration, 0, SimulationSetup::UPDATE_SPEED);
		std::this_thread::sleep_for(std::chrono::milliseconds(timeError));
	}	
}

void UpdateManager::Update() {

	PerformanceAnalyser::PushTime();
	CreatureManager::Update();
	PerformanceAnalyser::PopTime("CreatureManager update");

	SimulationManager::Update();
}

void UpdateManager::SDLUpdate() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			Quit();
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Quit();
		}

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT)
				InputManager::MouseLeftClick();
			if (event.button.button == SDL_BUTTON_RIGHT)
				InputManager::MouseRightClick();
			if (event.button.button == SDL_BUTTON_MIDDLE)
				InputManager::MouseWheelClick();
		}

		if (event.type == SDL_MOUSEMOTION) {
			int xMouse, yMouse;
			SDL_GetMouseState(&xMouse, &yMouse);
			InputManager::LastArenaMousePos = InputManager::ArenaMousePos;
			InputManager::LastScreenMousePos = InputManager::ScreenMousePos;
			InputManager::ScreenMousePos = Vector2(xMouse, yMouse);
			InputManager::ArenaMousePos = InputManager::ScreenMousePos.Mult(1 / PaintManager::ZoomLevel);
		}

		if (event.type == SDL_MOUSEWHEEL) {
			InputManager::MouseWheelSpun(event.wheel.y);
		}

		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			InputManager::MouseLeftHold();
		}
		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			InputManager::MouseRightHold();
		}
		if (SDL_GetMouseState(nullptr, nullptr) & SDL_BUTTON(SDL_BUTTON_MIDDLE)) {
			InputManager::MouseWheelHold();
		}
	}

	InputManager::Update();
}

void UpdateManager::Quit() {
	Running = false;
}
