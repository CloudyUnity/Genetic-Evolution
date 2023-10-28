#pragma once
#include <deque>

#ifndef UPDATEMANAGAER_H
#define UPDATEMANAGAER_H

class UpdateManager {
public:
    static double FPS;
    static std::deque<double> LastFrameDurations;

    static void BeginUpdateLoop();
    static void Update();
    static void SDLUpdate();
    static void Quit();    

    static bool Running;
    static int UpdatesSinceSimStart;
};

#endif // SHAPE_H
