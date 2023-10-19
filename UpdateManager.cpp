#include "UpdateManager.h"
#include <chrono>
#include <thread>
#include "Logger.h"
#include "Shape.h"
#include "Windows.h"
#include "PaintManager.h"
#include "SDL.h"

bool UpdateManager::Running;

void UpdateManager::BeginUpdateLoop() {

	UpdateManager::Start();

	Shape shape = Shape(5, 5, 200, 100);
	shape.Text = "Halo!";

	Running = true;

	const int SECONDS_TO_RUN = 10;
	int loops = SECONDS_TO_RUN * 100;

	for (int i = 0; i < loops && Running; i++) {
		Logger::Log("\nUpdate #" + std::to_string(i));

		UpdateManager::Update();

		shape.Col.AddColor(Color(0, 1, 0, 0));
		shape.Position.X += 1;
		Logger::Log(shape.Col.ToString());
		Logger::Log(shape.Position.X);

		PaintManager::Draw();

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	PaintManager::CleanUp();
}

void UpdateManager::Start() {

}

void UpdateManager::Update() {

	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			Quit();
		}

		if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
			Quit();
		}
	}
}

void UpdateManager::Quit() {
	Running = false;
}
