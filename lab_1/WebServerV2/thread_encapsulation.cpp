#include "thread_encapsulation.h"
#include "utils.h"

/**
 * @brief constructor
 */
ThreadEncapsulation::ThreadEncapsulation() {
    this->is_finished_ = false;
}

/**
 * @brief constructor
 * @param new_socket
 * @param ip_in
 */
void ThreadEncapsulation::CreateThread(int new_socket, std::string ip_in, HttpServer * output_server) {
    std::thread client(ClientThreadReceive, new_socket, ip_in, this, output_server); // new thread
    client.detach(); // 分发
}
