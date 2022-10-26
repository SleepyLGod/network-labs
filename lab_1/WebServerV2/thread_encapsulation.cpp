#include "thread_encapsulation.h"
#include "utils.h"

/**
 * @brief constructor
 */
ThreadEncapsulation::ThreadEncapsulation() {
    this->is_finished_ = false;
}

/**
 * @brief receive the data of the client
 * @param new_socket
 * @param ip_in
 * @param t
 */
void ClientThreadReceive(int new_socket, std::string ip_in, ThreadEncapsulation * t) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    Request request = Request(std::string(buffer));
    Response response = Response(request);
    std::string path = server_config::path + request.request_url_;
    UrlParser urlParser;
    if (request.request_url_ == "/")
        path = server_config::index;
    char file_buffer[255];
    if (!UrlParser::CheckPath(path)) { // 检测不通过，访问了上层目录
        response.set_status(400);
        urlParser = UrlParser(server_config::bad_request);
    } else {
        urlParser = UrlParser(path);
        if (urlParser.is_ok_) {
            response.set_status(200);
        } else {
            urlParser = UrlParser(server_config::not_found);
            response.set_status(404);
        }
    }
    LogPrint(response, request, ip_in);
    response.AddHeader("Content-Type", urlParser.file_type_);
    write(new_socket, response.ToString().c_str(), response.ToString().size()); // 写入返回头
    // 写入返回主体
    while (urlParser.file_.readsome(file_buffer, sizeof(file_buffer))) {
        write(new_socket, file_buffer, urlParser.file_.gcount());
    }
    close(new_socket);
    t->is_finished_ = true;
}

/**
 * @brief constructor
 * @param new_socket
 * @param ip_in
 */
void ThreadEncapsulation::CreateThread(int new_socket, std::string ip_in) {
    std::thread client(ClientThreadReceive, new_socket, ip_in, this); // new thread
    client.detach(); // 分发
}
