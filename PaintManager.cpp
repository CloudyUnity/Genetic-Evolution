#include "PaintManager.h"
#include "Logger.h"

std::vector<Shape*> PaintManager::ShapeList;
SDL_Window* PaintManager::Window;
SDL_Renderer* PaintManager::Rend;

void PaintManager::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		Logger::Log("ERROR: SDL was not initalized correctly");

	Window = SDL_CreateWindow("SDL Window EvoProj", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
	Rend = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
}

void PaintManager::Draw() {

	Logger::Log("\nStart drawing");

	SDL_SetRenderDrawColor(Rend, 0, 0, 0, 1);
	SDL_RenderClear(Rend);

	for (int i = 0; i < ShapeList.size(); i++) {
		Shape* shape = ShapeList.at(i);
		PaintManager::DrawShape(shape);
	}

	SDL_RenderPresent(Rend);
}

void PaintManager::DrawShape(Shape* shape) {

	if (shape == nullptr) {
		Logger::Log("Shape was found to be a null pointer");
		return;
	}

	SDL_Rect rect;
	rect.x = (int)shape->Position.X;
	rect.w = (int)shape->Scale.X;
	rect.y = (int)shape->Position.Y;
	rect.h = (int)shape->Scale.Y;

	SDL_SetRenderDrawColor(Rend, shape->Col.R, shape->Col.G, shape->Col.B, shape->Col.A);

	SDL_RenderFillRect(Rend, &rect);

	Logger::Log("Drawing shape \"" + shape->Text + "\" at: " + shape->Position.ToString());
}

void PaintManager::AddShape(Shape* shape) {
	PaintManager::ShapeList.push_back(shape);
}

void PaintManager::CleanUp() {
	SDL_DestroyRenderer(Rend);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}