#pragma once
#include "Vector2.h"
#include <iostream>
#include "PaintManager.h"
#include "Logger.h"

#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

class InputManager {
public:
	static Vector2 ArenaMousePos;
	static Vector2 LastArenaMousePos;
	static Vector2 ScreenMousePos;
	static Vector2 LastScreenMousePos;
	static Shape* MouseShape;
	static Shape* CurrentHoveredShape;

	static void Init();
	static void Update();

	static void MouseLeftClick();
	static void MouseRightClick();
	static void MouseLeftHold();
	static void MouseRightHold();
	static void MouseWheelSpun(int dir);
	static void MouseWheelClick();
	static void MouseWheelHold();
};

#endif
