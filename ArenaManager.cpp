#include "ArenaManager.h"

bool ArenaManager::WrapAround;
Color ArenaManager::ArenaColor;
Vector2 ArenaManager::ArenaSize;
Vector2 ArenaManager::MaxBounds;
Vector2 ArenaManager::MinBounds;

void ArenaManager::Init(Vector2 size, bool wrap, int wrapPad, Color color, bool wallsEnabled) {
	WrapAround = wrap;
	ArenaSize = size;
	MaxBounds = size;
	ArenaColor = color;

	if (wrap) {
		MaxBounds = MaxBounds.Add(wrapPad);
		MinBounds = Vector2(-wrapPad, -wrapPad);
	}		

	MakeArenaShapes();
	if (wallsEnabled)
		MakeWalls();
	MakeTokens();
}

void ArenaManager::MakeArenaShapes() {

	Shape::ShapeInfo info;
	info.Col = ArenaColor;
	info.Scale = MaxBounds.Sub(MinBounds);
	info.Position = MinBounds.Add(info.Scale.Mult(0.5));
	info.Layer = -5000;
	new Shape(info);

	double pad = 300;
	double halfPad = pad * 0.5;
	Vector2 center = info.Position;
	Vector2 scale = info.Scale;

	info = Shape::ShapeInfo();
	info.Col = SimulationSetup::BG_COLOR;
	info.Position = Vector2(center.X, MinBounds.Y - halfPad);
	info.Scale = Vector2(scale.X + pad * 2, pad);
	info.Layer = 3000;
	info.BorderSize = 15;
	info.BorderColor = Color::BLACK;
	new Collider(info, false, !WrapAround);

	info.Position = Vector2(center.X, MaxBounds.Y + halfPad);
	new Collider(info, false, !WrapAround);

	info.Position = Vector2(MaxBounds.X + halfPad, center.Y);
	info.Scale = Vector2(pad, scale.Y + pad * 2);
	new Collider(info, false, !WrapAround);

	info.Position = Vector2(MinBounds.X - halfPad, center.Y);
	new Collider(info, false, !WrapAround);
}

void ArenaManager::MakeWalls() {

	Shape::ShapeInfo info;
	info.Col = Color::COZY_BLACK;
	info.Layer = 1300;
	info.BorderSize = 15;
	info.BorderColor = Color::BLACK;
	info.Layer = 2900;

	// Square 1
	info.Position = Vector2(1000, 400);
	info.Scale = Vector2(300, 300);
	new Collider(info, false, true);

	// Square 2
	info.Position = Vector2(1400, 100);
	new Collider(info, false, true);

	// Square 3
	info.Position = Vector2(1800, 0);
	new Collider(info, false, true);

	// Square 5
	info.Position = Vector2(1800, 500);
	new Collider(info, false, true);

	// Tiny Square (6)
	info.Position = Vector2(2150, 250);
	info.Scale = Vector2(100, 100);
	new Collider(info, false, true);

	// Square 7
	info.Position = Vector2(2400, 50);
	info.Scale = Vector2(300, 300);
	new Collider(info, false, true);

	// Square 8
	info.Position = Vector2(2400, 450);
	new Collider(info, false, true);

	// Floor 1
	info.Position = Vector2(1250, 600);
	info.Scale = Vector2(2700, 200);
	info.Layer = 2950;
	new Collider(info, false, true);

	// Floor 2
	info.Position = Vector2(1600, 1200);
	info.Scale = Vector2(2600, 200);
	new Collider(info, false, true);

	// Side Wall
	info.Position = Vector2(3000, 600);
	info.Scale = Vector2(200, 1400);
	info.Layer = 2960;
	new Collider(info, false, true);

	// Diamond 1
	info.Position = Vector2(2500, 900);
	info.Scale = Vector2(200, 200);
	info.RotationAngle = 45;
	info.Layer = 2900;
	new Collider(info, false, true);

	// Diamond 2
	info.Position = Vector2(2300, 700);
	info.Scale = Vector2(150, 150);
	new Collider(info, false, true);

	// Diamond 3
	info.Position = Vector2(2300, 1100);
	new Collider(info, false, true);

	// Diamond 4
	info.Position = Vector2(2100, 900);
	info.Scale = Vector2(200, 200);
	new Collider(info, false, true);
}

void ArenaManager::MakeTokens() {

	Shape::ShapeInfo info;	
	info.Col = Color::COZY_RED;
	info.Layer = 1200;

	info.Position = Vector2(1000, 250);
	info.Scale = Vector2(20, 500);
	new RewardToken(info);

	info.Position = Vector2(1400, 250);
	new RewardToken(info);

	info.Position = Vector2(1800, 250);
	new RewardToken(info);

	info.Position = Vector2(2400, 250);
	new RewardToken(info);

	info.Position = Vector2(2300, 750);
	new RewardToken(info);

	info.Scale = Vector2(20, 600);	
	info.Position = Vector2(1700, 800);
	new RewardToken(info);

	info.Position = Vector2(2700, 500);
	info.Scale = Vector2(600, 20);
	new RewardToken(info);

	info.RotationAngle = 45;
	info.Position = Vector2(2700, 900);
	new RewardToken(info);
}