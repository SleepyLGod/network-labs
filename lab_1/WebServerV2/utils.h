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

void LogPrint(Response, Request, std::string);
void ClientThreadReceive(int, std::string, ThreadEncapsulation *, HttpServer *);
bool CheckIp(std::string);
bool CheckPath(std::string);
bool CheckPort(std::string);
bool CheckThreadLimit(std::string);

#endif // UTILS_H
