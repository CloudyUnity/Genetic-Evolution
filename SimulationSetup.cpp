#include "SimulationSetup.h"

const Vector2 SimulationSetup::MAX_BOUNDS(ARENA_SIZE_X + BOUNDS_PADDING, ARENA_SIZE_Y + BOUNDS_PADDING);
const Vector2 SimulationSetup::MIN_BOUNDS(0 - BOUNDS_PADDING, 0 - BOUNDS_PADDING);
const Vector2 SimulationSetup::WINDOW_BOUNDS(800, 600);

const float SimulationSetup::MAX_VISION_DISTANCE = 50.0;
const double SimulationSetup::CREATURE_FRICTION = 0.9;
const double SimulationSetup::HOVER_SIZE_INCREASE = 1.2;
const float SimulationSetup::CREATURE_OSS_PERIOD = 0.1;

const Color SimulationSetup::BG_COLOR = Color::COZY_BLACK;
const Color SimulationSetup::CREATURE_COLOR = Color::PINK;
const Color SimulationSetup::CREATURE_BORDER_COLOR = Color::BLACK;
const Color SimulationSetup::CREATURE_SELECTED_COLOR = Color::PURPLE;
const Color SimulationSetup::CREATURE_EYE_COLOR = Color::LIGHT_BLUE;
const Color SimulationSetup::CREATURE_EYE_BORDER_COLOR = Color::BLACK;
const Color SimulationSetup::HUD_BG_COLOR = Color::LIGHT_BLUE;
const Color SimulationSetup::HUD_BUTTON_COLOR = Color::COZY_WHITE;
const Color SimulationSetup::ARENA_COLOR = Color::COZY_WHITE;