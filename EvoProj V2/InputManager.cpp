#include "InputManager.h"
#include "CreatureManager.h"
#include "BrainViewer.h"
#include "SimulationSetup.h"

Vector2 InputManager::ArenaMousePos;
Vector2 InputManager::LastArenaMousePos;
Vector2 InputManager::ScreenMousePos;
Vector2 InputManager::LastScreenMousePos;
Shape* InputManager::MouseShape;
Shape* InputManager::CurrentHoveredShape;

void InputManager::Init() {
	Shape::ShapeInfo info;
	info.Scale = Vector2(10, 10);
	info.Col = Color(0, 0, 0, 100);
	info.Text = "Mouse";
	info.Layer = 1000;
	MouseShape = new Shape(info);
}

void InputManager::Update() {
	MouseShape->Info.Position = ArenaMousePos.Sub(PaintManager::Scroller->Info.Position);
	MouseShape->Info.Visible = SimulationSetup::MOUSE_SHAPE_VISIBLE;

	Vector2 arenaMousePos = MouseShape->Info.Position;
	for (int i = PaintManager::ShapeList.size() - 1; i >= 0; i--) {

		Shape* shape = PaintManager::ShapeList.at(i);

		if (!shape->Info.Hoverable)
			continue;

		bool arenaHovered = !shape->Info.ZoomDisabled && shape->Contains(arenaMousePos);
		bool hudHovered = shape->Info.ZoomDisabled && shape->Contains(ScreenMousePos);

		if (!arenaHovered && !hudHovered)
			continue;

		CurrentHoveredShape = shape;
		return;
	}
	CurrentHoveredShape = nullptr;
}

void InputManager::MouseLeftClick() {
	
	if (CurrentHoveredShape) {
		CurrentHoveredShape->OnMouseClick();
		return;
	}		
	
	BrainViewer::ClearOldBrain();
	CreatureManager::DeselectSelected();
}

void InputManager::MouseRightClick() {

}

void InputManager::MouseWheelSpun(int dir) {
	PaintManager::ZoomLevel += dir * 0.1;
}

void InputManager::MouseRightHold() {

}

void InputManager::MouseLeftHold() {

}

void InputManager::MouseWheelClick() {

}

void InputManager::MouseWheelHold() {
	Vector2 dir = ArenaMousePos.Sub(LastArenaMousePos);
	if (dir.Magnitude() > 0.1)
		PaintManager::MoveScroller(dir);
}