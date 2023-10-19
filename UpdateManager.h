#pragma once

#ifndef UPDATEMANAGAER_H
#define UPDATEMANAGAER_H

class UpdateManager {
public:
    static void BeginUpdateLoop();
    static void Update();
    static void Start();
    static void Quit();
    static bool Running;
};

#endif // SHAPE_H
