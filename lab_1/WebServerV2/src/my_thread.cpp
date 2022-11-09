#include "../include/my_thread.h"

#include "../include/utils.h"
#include "../include/Request.h"
using namespace std;
void my_thread::create_thread(int new_socket, string ip_in, http_server * output_server) {
    thread client(client_thread, new_socket, ip_in, this, output_server); // 创建一个新的线程
    client.detach(); // 分发
}

my_thread::my_thread() {
    this->finished = false;
}
