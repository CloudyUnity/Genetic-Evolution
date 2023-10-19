#pragma once

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>
#include <fstream>

class Logger {
public:
    static void Init();
    template <typename T>
    static void Log(T logMessage);
    static void ClearFile();

private:
    static std::string FilePath;
};

template <typename T>
void Logger::Log(T logMessage) {
    std::ofstream outputFile(FilePath, std::ios::app);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    outputFile << logMessage << std::endl;
    outputFile.close();
}

#endif // LOGGER_H
