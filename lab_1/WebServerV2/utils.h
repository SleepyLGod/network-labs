#ifndef UTILS_H
#define UTILS_H

#include <chrono>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>
#include <unistd.h>
#include "thread_encapsulation.h"

bool CheckIp(std::string);
bool CheckPath(std::string);
bool CheckPort(std::string);
bool CheckThreadLimit(std::string);
void LogPrint(Response, Request, std::string);

#endif // UTILS_H
