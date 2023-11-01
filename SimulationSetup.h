#pragma once
#include "Vector2.h"
#include "Color.h"

#ifndef SIMULATION_SETUP_H
#define SIMULATION_SETUP_H

class SimulationSetup {
public:
    static const int UPDATE_SPEED = 10;
    static const bool LIMITED_PROGRAM_TIME = false;
    static const int FRAMERATE_FRAME_COUNT = 30;   
    static const Vector2 WINDOW_BOUNDS;

    static const float MAX_VISION_DISTANCE;
    static const float CREATURE_OSS_PERIOD;
    static const double CREATURE_FRICTION;
    static const bool CREATURE_COLLISION_ON = true;
    static const double CREATURE_SPEED_MULT;
    static const double CREATURE_ROTATION_MULT;
    static const bool REWARD_TOKEN_SPEED_BONUS = true;

    static const int NO_MUTATION_BEST_OF_COUNT = 10; // The nth best creatures get added to next gen with no mutations

    static const Color BG_COLOR;
    static const Color CREATURE_COLOR;
    static const Color CREATURE_BORDER_COLOR;
    static const Color CREATURE_SELECTED_COLOR;
    static const Color CREATURE_EYE_COLOR;
    static const Color CREATURE_EYE_BORDER_COLOR;
    static const Color HUD_BG_COLOR;
    static const Color HUD_BUTTON_COLOR;

    static const bool MOUSE_SHAPE_VISIBLE = false;
    static const bool TEXT_RENDERING = true;
    static const bool TEXT_RESCALING_ON = true;
    static const int TEXT_QUALITY = 30;
    static const double HOVER_SIZE_INCREASE;
};

#endif 
