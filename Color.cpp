#include "Color.h"
#include <algorithm>
#include <vector>
#include <string>

const Color Color::BLACK = Color(0, 0, 0, 255);
const Color Color::WHITE = Color(255, 255, 255, 255);
const Color Color::RED = Color(255, 0, 0, 255);
const Color Color::GREEN = Color(0, 255, 0, 255);
const Color Color::BLUE = Color(0, 0, 255, 255);
const Color Color::TRANS = Color(0, 0, 0, 0);
const Color Color::PINK = Color(0xF875AA);
const Color Color::PEACH = Color(0xFFDFDF);
const Color Color::COZY_WHITE = Color(0xFFF6F6);
const Color Color::LIGHT_BLUE = Color(0xAEDEFC);
const Color Color::PURPLE = Color(0x610C9F);
const Color Color::CREAM = Color(0xFFDBAA);
const Color Color::COZY_RED = Color(0xF31559);
const Color Color::COZY_BLACK = Color(0x2B2730);

Color::Color(int r1, int g1, int b1, int a1) {
	R = r1;
	G = g1;
	B = b1;
	A = a1;
}

Color::Color(int hex) {
	R = (hex & 0xFF0000) >> 16;
	G = (hex & 0x00FF00) >> 8;
	B = (hex & 0x0000FF);
	A = 255;
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

SDL_Color Color::ToSDLColor() {
	SDL_Color sdlCol;
	sdlCol.r = R;
	sdlCol.g = G;
	sdlCol.b = B;
	sdlCol.a = A;
	return sdlCol;
}