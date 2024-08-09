#include "PerformanceAnalyser.h"
#include "Logger.h"

std::stack<std::chrono::system_clock::time_point> PerformanceAnalyser::Stack;

void PerformanceAnalyser::PushTime() {
	
	auto currentTime = std::chrono::system_clock::now();
	Stack.push(currentTime);
}

long long PerformanceAnalyser::PopTime(std::string label) {

	std::chrono::system_clock::time_point pushedTime = Stack.top();
	Stack.pop();

	auto currentTime = std::chrono::system_clock::now();

	std::chrono::milliseconds duration = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - pushedTime);

	long long milliseconds = duration.count();

	std::string s = "";
	for (int i = 0; i < Stack.size(); i++)
		s += "=";

	Logger::Log(s + label + " took " + std::to_string(milliseconds) + " milliseconds!");

	return milliseconds;
}