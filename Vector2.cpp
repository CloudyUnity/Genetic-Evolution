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

Vector2 Vector2::Mult(double multiplier) {
	Vector2 newVec = Vector2(X, Y);
	newVec.X *= multiplier;
	newVec.Y *= multiplier;
	return newVec;
}

Vector2 Vector2::Add(Vector2 other) {
	Vector2 newVec = Vector2(X, Y);
	newVec.X += other.X;
	newVec.Y += other.Y;
	return newVec;
}

Vector2 Vector2::Add(double x1, double y1) {
	return Vector2(X + x1, Y + y1);
}

Vector2 Vector2::Add(double a) {
	return Vector2(X + a, Y + a);
}

Vector2 Vector2::Sub(Vector2 other) {
	Vector2 newVec = Vector2(X, Y);
	newVec.X -= other.X;
	newVec.Y -= other.Y;
	return newVec;
}

Vector2 Vector2::Sub(double x1, double y1) {
	return Vector2(X - x1, Y - y1);
}

Vector2 Vector2::Clone() {
	return Vector2(X, Y);
}

double Vector2::Area(Vector2 A, Vector2 B, Vector2 C) {
	return abs((B.X * A.Y - A.X * B.Y) + (C.X * B.Y - B.X * C.Y) + (A.X * C.Y - C.X * A.Y)) * 0.5;
}

float Vector2::DotProduct(Vector2 other) {
	return (X * other.X) + (Y * other.Y);
}

double Vector2::Magnitude() {
	return (sqrt(X * X + Y * Y));
}

Vector2 Vector2::Normalized() {
	return Mult(1 / Magnitude());
}

Vector2 Vector2::RoundToNearest(double rounder) {
	return Vector2(round(X / rounder) * rounder, round(Y / rounder) * rounder);
}
