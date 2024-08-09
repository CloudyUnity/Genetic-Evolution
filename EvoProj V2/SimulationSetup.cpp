#include "SimulationSetup.h"

const Vector2 SimulationSetup::WINDOW_BOUNDS(1200, 700);

const float SimulationSetup::MAX_VISION_DISTANCE = 150.0;
const double SimulationSetup::CREATURE_FRICTION = 0.9;
const double SimulationSetup::HOVER_SIZE_INCREASE = 1.2;
const double SimulationSetup::CREATURE_SPEED_MULT = 1.1;
const double SimulationSetup::CREATURE_ROTATION_MULT = 2.0;
const float SimulationSetup::CREATURE_OSS_PERIOD = 0.1;

const Color SimulationSetup::BG_COLOR = Color::COZY_BLACK;
const Color SimulationSetup::CREATURE_COLOR = Color::PINK;
const Color SimulationSetup::CREATURE_BORDER_COLOR = Color::BLACK;
const Color SimulationSetup::CREATURE_SELECTED_COLOR = Color::PURPLE;
const Color SimulationSetup::CREATURE_EYE_COLOR = Color::LIGHT_BLUE;
const Color SimulationSetup::CREATURE_EYE_BORDER_COLOR = Color::BLACK;
const Color SimulationSetup::HUD_BG_COLOR = Color::LIGHT_BLUE;
const Color SimulationSetup::HUD_BUTTON_COLOR = Color::COZY_WHITE;