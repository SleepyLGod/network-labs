#include "Request.h"
#include "Response.h"
#include <chrono>
#include <ctime>
#include <vector>
#include <thread>
#include <mutex>
#include "my_thread.h"
#ifndef SOCKET_UTILS_H
#define SOCKET_UTILS_H

void print_log(Response, Request, string);
void client_thread(int , string, my_thread *, http_server *);
bool check_ip(string ip);
bool check_port(string port);
bool check_path(string path);
bool check_thread_limit(string thread_limit);
#endif //SOCKET_UTILS_H
