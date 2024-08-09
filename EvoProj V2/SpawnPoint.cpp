#include "SpawnPoint.h"

Vector2 SpawnPoint::Pos;
bool SpawnPoint::Active;

void SpawnPoint::Set(Vector2 pos) {
	Active = true;
	Pos = pos;
}