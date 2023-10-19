#include "Vector2.h"
#include <string>

Vector2::Vector2(double x1, double y1) {
	X = x1;
	Y = y1;
}

Vector2::Vector2() : X(), Y() {

}

std::string Vector2::ToString() {
	return "(" + std::to_string(X) + ", " + std::to_string(Y) + ")";
}
