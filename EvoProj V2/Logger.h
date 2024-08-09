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

    template <typename T>
    static void AltLog(T logMessage);

    template <typename T>
    static void HardLog(T logMessage, std::string fileName);

    static void ClearFile();
    static void CloseStream();

    static std::ofstream OutputStream;
    static std::ofstream AltOutputStream;

    static std::string FilePath;
    static std::string AltFilePath;
};

template <typename T>
void Logger::Log(T logMessage) {

    if (!OutputStream.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    OutputStream << logMessage << std::endl;
}

template <typename T>
void Logger::AltLog(T logMessage) {

    if (!AltOutputStream.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    AltOutputStream << logMessage << std::endl;
}

template <typename T>
void Logger::HardLog(T logMessage, std::string fileName) {

    std::string filePath = "C:\\Users\\finnw\\OneDrive\\Documents\\EvoProjSavedFiles\\" + fileName + ".txt";
    std::ofstream outputStream(filePath);

    if (!outputStream.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    outputStream << "";
    outputStream = std::ofstream(filePath, std::ios::app);

    outputStream << logMessage << std::endl;
    outputStream.close();
}

#endif // LOGGER_H
