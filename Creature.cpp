#include "Creature.h"

Creature::Creature(ShapeInfo info, int inC, int gS) : Shape(info) {
	Brain.Init(inC, gS);

	Info.Layer = rand() % 1000;

	InitEyes();

	CreatureManager::AddToCreatureList(this);
}

Creature::Creature(ShapeInfo info, int inC, std::vector<int> genes) : Shape(info) {
	Brain.Init(inC, genes);

	Info.Layer = rand() % 1000;

	InitEyes();

	CreatureManager::AddToCreatureList(this);
}

void Creature::InitEyes() {
	Shape::ShapeInfo eyeInfo;
	eyeInfo.Position = Vector2(10, 4);
	eyeInfo.Scale = Vector2(5, 5);
	eyeInfo.Col = SimulationSetup::CREATURE_EYE_COLOR;
	eyeInfo.Layer = Info.Layer + 1;
	eyeInfo.Text = "Eye";
	eyeInfo.BorderColor = SimulationSetup::CREATURE_EYE_BORDER_COLOR;
	eyeInfo.BorderSize = 2;
	eyeInfo.QuickDrawDisabled = true;

	eye1 = new Shape(eyeInfo);
	eye1->Parent = (Shape*)this;

	eyeInfo.Position = Vector2(10, -4);
	eye2 = new Shape(eyeInfo);
	eye2->Parent = (Shape*)this;
}

void Creature::Update() {
	Brain.Update(this);
	Move();
}

void Creature::AddAccelerationForward(double amount) {
	Velocity = Velocity.Add(GetPointDirection().Mult(amount));
}

void Creature::Move() {
	if (Velocity.X == 0 && Velocity.Y == 0)
		return;

	Vector2 newPos = Info.Position.Add(Velocity);
	Velocity = Velocity.Mult(SimulationSetup::CREATURE_FRICTION);
	if (Velocity.Magnitude() < 0.01)
		Velocity = Vector2(0, 0);

	Vector2 max = SimulationSetup::MAX_BOUNDS;
	max = max.Add(SimulationSetup::SCREEN_WRAP_PADDING);
	Vector2 min = SimulationSetup::MIN_BOUNDS;
	min = min.Add(-SimulationSetup::SCREEN_WRAP_PADDING);

	if (newPos.X > max.X) {
		double displacement = newPos.X - max.X;
		newPos.X = min.X + displacement;
	}
	if (newPos.Y > max.Y) {
		double displacement = newPos.Y - max.Y;
		newPos.Y = min.Y + displacement;
	}
	if (newPos.X < min.X) {
		double displacement = newPos.X - min.X;
		newPos.X = max.X + displacement;
	}
	if (newPos.Y < min.Y) {
		double displacement = newPos.Y - min.Y;
		newPos.Y = max.Y + displacement;
	}

	Info.Position = newPos;
}

void Creature::Rotate(double amount) {
	Info.RotationAngle += amount;
}

void Creature::Die() {
	PaintManager::RemoveShape(this);
}

bool Creature::CheckCollision(Creature* otherCreature) {

	double distance = sqrt(pow(Info.Position.X - otherCreature->Info.Position.X, 2) + pow(Info.Position.Y - otherCreature->Info.Position.Y, 2));
	if (distance > 28.28427125) // 2 * radius based on Creatures with scale (20, 10)
		return false;

	double dx = otherCreature->Info.Position.X - Info.Position.X;
	double dy = otherCreature->Info.Position.Y - Info.Position.Y;

	double minSeparationX = (Info.HalfScale.X + otherCreature->Info.HalfScale.X) - abs(dx);
	double minSeparationY = (Info.HalfScale.Y + otherCreature->Info.HalfScale.Y) - abs(dy);

	if (minSeparationX <= 0 || minSeparationY <= 0)
		return false;

	if (minSeparationX < minSeparationY) {
		double moveX = minSeparationX * (dx < 0 ? -1 : 1) / 2.0;
		Info.Position.X -= moveX;
		otherCreature->Info.Position.X += moveX;
	}
	else {
		double moveY = minSeparationY * (dy < 0 ? -1 : 1) / 2.0;
		Info.Position.Y -= moveY;
		otherCreature->Info.Position.Y += moveY;
	}

	return true;
}

bool Creature::CheckCollision(Shape* wall) {

	double distance = sqrt(pow(Info.Position.X - wall->Info.Position.X, 2) + pow(Info.Position.Y - wall->Info.Position.Y, 2));
	double wallRadius = sqrt(pow(wall->Info.HalfScale.X, 2) + pow(wall->Info.Scale.Y, 2));
	if (distance > wallRadius + 14.14213562)
		return false;

	double dx = wall->Info.Position.X - Info.Position.X;
	double dy = wall->Info.Position.Y - Info.Position.Y;

	double minSeparationX = (Info.HalfScale.X + wall->Info.HalfScale.X) - abs(dx);
	double minSeparationY = (Info.HalfScale.Y + wall->Info.HalfScale.Y) - abs(dy);

	if (minSeparationX <= 0 || minSeparationY <= 0)
		return false;

	if (minSeparationX < minSeparationY) {
		double moveX = minSeparationX * (dx < 0 ? -1 : 1);
		Info.Position.X -= moveX;
	}
	else {
		double moveY = minSeparationY * (dy < 0 ? -1 : 1);
		Info.Position.Y -= moveY;
	}

	return true;
}

void Creature::OnMouseClick() {

	bool deselectSelf = CreatureManager::SelectedCreature == this;

	CreatureManager::DeselectSelected();

	if (deselectSelf) {
		BrainViewer::ClearOldBrain();
		return;
	}

	CreatureManager::SetSelected(this);
	BrainViewer::DisplayBrain(Brain);
}