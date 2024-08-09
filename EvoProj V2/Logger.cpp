#include "Logger.h"
#include <iostream>
#include <fstream>

std::string Logger::FilePath;
std::string Logger::AltFilePath; 
std::ofstream Logger::OutputStream;
std::ofstream Logger::AltOutputStream;

void Logger::Init() {

    FilePath = "..\\Data\\debugLog.txt";
    OutputStream = std::ofstream(FilePath, std::ios::app);    

    AltFilePath = "..\\Data\\debugLogAlt.txt";
    AltOutputStream = std::ofstream(AltFilePath, std::ios::app);

    Logger::ClearFile();
}

void Logger::ClearFile() {

    std::ofstream outputFile(FilePath);
    std::ofstream outputFileAlt(AltFilePath);

    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file for appending." << std::endl;
        return;
    }

    outputFile << "";
    outputFile.close();

    outputFileAlt << "";
    outputFileAlt.close();
}

void Logger::CloseStream() {
    OutputStream.close();
    AltOutputStream.close();
}
