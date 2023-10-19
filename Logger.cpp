#include "Logger.h"
#include <iostream>
#include <fstream>

std::string Logger::FilePath; // Define the static member variable

void Logger::Init() {
    FilePath = "C:\\Users\\finnw\\OneDrive\\Documents\\EvoProjSavedFiles\\debugLog.txt";

    Logger::ClearFile();
}

void Logger::ClearFile() {

    std::ofstream outputFile(FilePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    outputFile << "";
    outputFile.close();
}
