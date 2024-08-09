#include "PaintManager.h"
#include "Logger.h"
#include "SimulationSetup.h"
#include "InputManager.h"
#include "SimulationManager.h"

std::vector<Shape*> PaintManager::ShapeList;
SDL_Window* PaintManager::Window;
SDL_Renderer* PaintManager::Rend;
SDL_Texture* PaintManager::Texture;
double PaintManager::ZoomLevel;
Shape* PaintManager::Scroller;
TTF_Font* PaintManager::MainFont;

void PaintManager::Init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		Logger::Log("ERROR: SDL was not initalized correctly");

	Window = SDL_CreateWindow("Evolution Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SimulationSetup::WINDOW_BOUNDS.X, SimulationSetup::WINDOW_BOUNDS.Y, SDL_WINDOW_SHOWN);
	Rend = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	Texture = LoadTexture("Blank");
	TTF_Init();
	MainFont = TTF_OpenFont("Data\\Rubik Fonts\\Rubik-Black.ttf", SimulationSetup::TEXT_QUALITY);

	if (!MainFont)
		throw std::exception("Error: Font not initialized correctly!");

	Shape::ShapeInfo info;
	info.Visible = false;
	Scroller = new Shape(info);

	ZoomLevel = 1;
}

void PaintManager::Draw() {

	Logger::Log("Drawing " + std::to_string(ShapeList.size()) + " shapes");

	Color bg = SimulationSetup::BG_COLOR;
	SDL_SetRenderDrawColor(Rend, bg.R, bg.G, bg.B, bg.A);
	SDL_RenderClear(Rend);

	for (int i = 0; i < ShapeList.size(); i++) {
		Shape* shape = ShapeList.at(i);
		if (!shape->Info.Visible)
			continue;
		if (shape->Info.QuickDrawDisabled && SimulationManager::UpdatesPerFrame > 1)
			continue;
		PaintManager::DrawShape(shape);
	}

	SDL_RenderPresent(Rend);
}

void PaintManager::DrawShape(Shape* shape) {

	if (shape == nullptr) {
		Logger::Log("Shape was found to be a null pointer");
		return;
	}

	if (shape->Info.IsLine) {
		DrawLine(shape);
		return;
	}

	Vector2 halfScale = shape->Info.HalfScale;
	Vector2 scale = shape->Info.Scale;
	Vector2 pos = shape->Info.Position;

	if (shape->Info.ConnectedToEastWindowEdge)
		pos.X += SimulationSetup::WINDOW_BOUNDS.X;

	if (shape->Info.ConnectedToSouthWindowEdge)
		pos.Y += SimulationSetup::WINDOW_BOUNDS.Y;

	if (!shape->Info.ZoomDisabled) {
		pos = pos.Mult(ZoomLevel);
		halfScale = halfScale.Mult(ZoomLevel);
		scale = scale.Mult(ZoomLevel);
	}

	if (InputManager::CurrentHoveredShape == shape) {
		scale = scale.Mult(SimulationSetup::HOVER_SIZE_INCREASE);
		halfScale = halfScale.Mult(SimulationSetup::HOVER_SIZE_INCREASE);
	}

	int rotationAngle = shape->Info.RotationAngle;
	Shape* parent = shape->Parent;
	while (parent != nullptr) {
		double angle = parent->Info.RotationAngle * (M_PI / 180.0);
		double rotatedX = pos.X * cos(angle) - pos.Y * sin(angle);
		double rotatedY = pos.X * sin(angle) + pos.Y * cos(angle);

		Vector2 parPos = parent->Info.Position;
		if (!parent->Info.ZoomDisabled)
			parPos = parPos.Mult(ZoomLevel);
		pos = parPos.Add(Vector2(rotatedX, rotatedY));

		rotationAngle += parent->Info.RotationAngle;
		parent = parent->Parent;
	}

	SDL_Rect rect;
	rect.x = (int)(pos.X - halfScale.X);
	rect.w = (int)scale.X;
	rect.y = (int)(pos.Y - halfScale.Y);
	rect.h = (int)scale.Y;

	SDL_Point pivot = { halfScale.X, halfScale.Y };
	SDL_Rect srcRect = { 0, 0, halfScale.X, halfScale.Y };

	if (shape->Info.BorderSize != 0) {

		SDL_SetTextureColorMod(Texture, shape->Info.BorderColor.R, shape->Info.BorderColor.G, shape->Info.BorderColor.B);
		SDL_SetTextureAlphaMod(Texture, shape->Info.BorderColor.A);

		SDL_RenderCopyEx(Rend, Texture, &srcRect, &rect, rotationAngle, &pivot, SDL_FLIP_NONE);

		double offset = shape->Info.BorderSize * 0.25;
		if (!shape->Info.ZoomDisabled)
			offset *= ZoomLevel;

		rect.x += offset;
		rect.w -= offset * 2;
		rect.h -= offset * 2;
		rect.y += offset;

		halfScale = Vector2(rect.w, rect.h).Mult(0.5);
		pivot = { (int)halfScale.X, (int)halfScale.Y };
	}
	
	SDL_SetTextureColorMod(Texture, shape->Info.Col.R, shape->Info.Col.G, shape->Info.Col.B);
	SDL_SetTextureAlphaMod(Texture, shape->Info.Col.A);	
	
	if (shape->Info.Col.A != 0)
		SDL_RenderCopyEx(Rend, Texture, &srcRect, &rect, rotationAngle, &pivot, SDL_FLIP_NONE);

	if (shape->Info.RenderText && !shape->Info.Text.empty() && SimulationSetup::TEXT_RENDERING)
		DrawTxt(shape, pos.Add(0, 0.5), halfScale);

	//Logger::Log("Drawing shape \"" + shape->Info.Text + "\" at: " + shape->Info.Position.ToString());
}

void PaintManager::DrawLine(Shape* shape) {
	Vector2 start = shape->Info.Position.Mult(ZoomLevel);
	Vector2 end = shape->Info.LineEndPosition.Mult(ZoomLevel);

	Shape* parent = shape->Parent;
	while (parent != nullptr) {
		double angle = parent->Info.RotationAngle * (M_PI / 180.0);

		double rotatedX = start.X * cos(angle) - start.Y * sin(angle);
		double rotatedY = start.X * sin(angle) + start.Y * cos(angle);
		start = parent->Info.Position.Mult(ZoomLevel).Add(Vector2(rotatedX, rotatedY));

		rotatedX = end.X * cos(angle) - end.Y * sin(angle);
		rotatedY = end.X * sin(angle) + end.Y * cos(angle);
		end = parent->Info.Position.Mult(ZoomLevel).Add(Vector2(rotatedX, rotatedY));

		parent = parent->Parent;
	}

	SDL_SetRenderDrawColor(Rend, shape->Info.Col.R, shape->Info.Col.G, shape->Info.Col.B, shape->Info.Col.A);
	SDL_RenderDrawLine(Rend, start.X, start.Y, end.X, end.Y);

	//Logger::Log("Drawing line from " + shape->Info.Position.ToString() + " to " + shape->Info.LineEndPosition.ToString());
}

void PaintManager::DrawTxt(Shape* shape, Vector2 pos, Vector2 scale) {

	if (!shape->Info.CachedSurface)
		shape->Info.CachedSurface = TTF_RenderText_Blended(MainFont, shape->Info.Text.c_str(), shape->Info.TextColor.ToSDLColor());

	if (!shape->Info.CachedSurface)
		return;

	if (!shape->Info.CachedTex)
		shape->Info.CachedTex = SDL_CreateTextureFromSurface(Rend, shape->Info.CachedSurface);

	if (!shape->Info.CachedTex)
		return;
	
	Vector2 scaled = Vector2(shape->Info.CachedSurface->w, shape->Info.CachedSurface->h);

	if (SimulationSetup::TEXT_RESCALING_ON && shape->Info.CachedSurface->w > scale.X) {
		double ratio = min(scale.X / shape->Info.CachedSurface->w, scale.Y / shape->Info.CachedSurface->h);
		scaled = scaled.Mult(ratio * 1.5);
	}	

	SDL_Rect rect;
	rect.x = (int)(pos.X - scaled.X * 0.5);	
	rect.y = (int)(pos.Y - scaled.Y * 0.5);
	rect.w = scaled.X;
	rect.h = scaled.Y;	

	SDL_RenderCopy(Rend, shape->Info.CachedTex, NULL, &rect);
}

void PaintManager::AddShape(Shape* shape) {
	for (int i = 0; i < ShapeList.size(); i++) {
		if (ShapeList.at(i)->Info.Layer > shape->Info.Layer) {
			ShapeList.insert(ShapeList.begin() + i, shape);
			return;
		}			
	}	
	ShapeList.push_back(shape);
}

void PaintManager::RemoveShape(Shape* shape) {

	if (!shape)
		return;

	for (int i = ShapeList.size() - 1; i >= 0; i--) {
		if (ShapeList.at(i) == shape) {
			if (shape->Info.CachedSurface)
				SDL_FreeSurface(shape->Info.CachedSurface);
			if (shape->Info.CachedTex)
				SDL_DestroyTexture(shape->Info.CachedTex);

			ShapeList.erase(ShapeList.begin() + i);
			break;
		}
	}

	delete shape;	
}

void PaintManager::CleanUp() {
	TTF_CloseFont(MainFont);
	TTF_Quit();

	SDL_DestroyRenderer(Rend);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}

SDL_Texture* PaintManager::LoadTexture(const char* imageName) {

	const char* basePath = "Data\\";
	const char* fileExtension = ".bmp";
	char fullPath[1024];
	snprintf(fullPath, sizeof(fullPath), "%s%s%s", basePath, imageName, fileExtension);

	SDL_Surface* surface = SDL_LoadBMP(fullPath);
	if (!surface) {
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(Rend, surface);
	SDL_FreeSurface(surface);
	return texture;
}

void PaintManager::DeallocAll() {
	for (int i = ShapeList.size(); i >= 0; i--) {
		delete ShapeList.at(i);
	}
}

void PaintManager::MoveScroller(Vector2 dir) {
	Scroller->Info.Position = Scroller->Info.Position.Add(dir);
}