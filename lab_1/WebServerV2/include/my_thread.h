#ifndef SOCKET_MY_THREAD_H
#define SOCKET_MY_THREAD_H
#include <thread>
#include <mutex>
#include "http_server.h"
using namespace std;

class my_thread {
public:
    bool finished;
    bool added;
    int flag;
    my_thread();
    void create_thread(int , string, http_server *);
};


#endif //SOCKET_MY_THREAD_H
