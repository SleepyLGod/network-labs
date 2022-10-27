#include "utils.h"

/**
 * @brief print logs after response
 * @param response
 * @param request
 * @param ip
 */
void LogPrint(Response response, Request request, std::string ip, HttpServer * output_server) {
    if (request.request_type_ == "") return ;
    auto current = std::chrono::system_clock::now();
    auto current_time = std::chrono::system_clock::to_time_t(current);
    auto out_put_time = std::string(ctime(&current_time));
    out_put_time = out_put_time.substr(0, out_put_time.size() - 1); // 去掉换行符
    output_server->Print(ip +
                         " - -" +
                         " [" +
                         out_put_time +
                         "] \" " +
                         request.request_type_ + " " +
                         request.request_url_ + "    " +
                         request.http_version_ +
                         "\" " +
                         std::to_string(response.response_status_) +
                         " - \n");
    std::cout << ip << " - - "
             << " [" << out_put_time << "] \" "
             << request.request_type_ << " "
             << request.request_url_ << " "
             << request.http_version_ << "\""
             << response.response_status_ << " - " << std::endl;
}

/**
 * @brief receive the data of the client
 * @param new_socket
 * @param ip_in
 * @param t
 */
void ClientThreadReceive(int new_socket, std::string ip_in, ThreadEncapsulation * t, HttpServer * output_server) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);

    Request request = Request(std::string(buffer));
    Response response = Response(request);
    std::string path = output_server->get_base_path() + request.request_url_;
    UrlParser urlParser;
    if (request.request_url_ == "/")
        path = server_config::index;
    char file_buffer[255];
    if (!UrlParser::CheckPath(path, output_server->get_base_path())) { // 检测不通过，访问了上层目录
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
    LogPrint(response, request, ip_in, output_server);
    response.AddHeader("Content-Type", urlParser.file_type_);
    write(new_socket, response.ToString().c_str(), response.ToString().size()); // 写入返回头
    // 写入返回主体
    while (urlParser.file_.readsome(file_buffer, sizeof(file_buffer)))
        write(new_socket, file_buffer, urlParser.file_.gcount());
    close(new_socket);
    t->is_finished_ = true;
}

bool CheckIp(std::string ip) {
    if (ip == "") return false;
    std::string left;
    std::string right;
    for (int i = 0; i < 3; i++) {
        if (ip.find(".") == std::string::npos) return false;
        left = ip.substr(0, ip.find("."));
        right = ip.substr(ip.find(".") + 1, ip.size());
        if (left.size() == 0 || right.size() == 0) return false;
        int value = stoi(left);
        if (value < 0 || value > 255) return false;
        ip = right;
    }
    int value = stoi(ip);
    if (value < 0 || value > 255) return false;
    return true;
}

bool CheckPath(std::string path) {
    if (path == "") return false;
    UrlParser tmp(path);
    return tmp.is_ok_;
}

bool CheckPort(std::string port) {
    if (port == "") return false;
    int tmp = stoi(port);
    return tmp > 0 && tmp < 65535;
}

bool CheckThreadLimit(std::string thread_limit) {
    int limit = stoi(thread_limit);
    return limit > 0 && limit <= server_config::max_thread_num;
}
