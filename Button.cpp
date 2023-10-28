#include "Button.h"
#include "Logger.h"

Button::Button(ShapeInfo info, std::function<void()> func) : Shape(info) {
	TriggerFunc = func;	
}

void Button::OnMouseClick() {
	if (TriggerFunc)
		TriggerFunc();
}