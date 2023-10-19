#include "Color.h"
#include <algorithm>
#include <vector>
#include <string>

Color::Color(int r1, int g1, int b1, int a1) {
	R = r1;
	G = g1;
	B = b1;
	A = a1;
}

Color::Color() {

}

uint32_t Color::RGBAValue() {
	int r = std::clamp(R, 0, 255);
	int g = std::clamp(G, 0, 255);
	int b = std::clamp(B, 0, 255);
	int a = std::clamp(A, 0, 255);

	uint32_t color = 0;
	color |= a << 24;
	color |= b << 16;
	color |= g << 8;
	color |= r;

	return color;
}

void Color::AddColor(Color color) {
	const int MAX_COLOR_VAL = 255;
	R = std::clamp(R + color.R, 0, MAX_COLOR_VAL);
	G = std::clamp(G + color.G, 0, MAX_COLOR_VAL);	
	B = std::clamp(B + color.B, 0, MAX_COLOR_VAL);	
	A = std::clamp(A + color.A, 0, MAX_COLOR_VAL);	
}

std::string Color::ToString() {
	return "(" + std::to_string(R) + ", " + std::to_string(G) + ", " + std::to_string(B) + ", " + std::to_string(A) + ")";
}