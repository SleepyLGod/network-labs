#include <iostream>
#include <unistd.h>

#include "../include/utils.h"
#include "../include/Request.h"
#include "../include/Response.h"
#include "../include/Fs.h"
#include "../include/my_thread.h"

using namespace std;

void print_log(Response response, Request request, string ip, http_server * output_server) {
    if (request.type == "") return ;
    auto current = chrono::system_clock::now();
    auto current_time = chrono::system_clock::to_time_t(current);
    auto out_put_time = string(ctime(&current_time));
    out_put_time = out_put_time.substr(0, out_put_time.size() - 1); // 去掉换行符
    output_server->print(ip +
                         " - -" +
                         " [" +
                         out_put_time +
                         "] \" " +
                         request.type + " " +
                         request.url + "    " +
                         request.http_version +
                         "\" " +
                         to_string(response.status) +
                         " - \n");
    cout << ip << " - - "
         << " [" << out_put_time << "] \" "
         << request.type << " "
         << request.url << " "
         << request.http_version << "\""
         << response.status << " - " << endl;
}

/*
 * 接收客户端的数据
 * */
void client_thread(int new_socket, string ip_in, my_thread * t, http_server * output_server) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);

    Request request = Request(string(buffer));
    Response response = Response(request);
    string path = output_server->get_base_path() + request.url;
    Fs fs;
    if (request.url == "/") path = INDEX;
    char file_buffer[255];
    if (!Fs::check_path(path, output_server->get_base_path())) { // 如果检测不通过，访问了上级目录
        response.set_status(400);
        fs = Fs(BAD_REQUEST);
    } else {
        fs = Fs(path);
        if (fs.ok) {
            response.set_status(200);
        } else {
            fs = Fs(NOT_FIND);
            response.set_status(404);
        }
    }
//    m.lock();
    print_log(response, request, ip_in, output_server);
//    m.unlock();
    response.add_header("Content-Type", fs.file_type);
    write(new_socket, response.to_string().c_str(), response.to_string().size()); // 写入返回头
    // 写入返回主体
    while(fs.file.readsome(file_buffer, sizeof(file_buffer)))
        write(new_socket, file_buffer, fs.file.gcount());
    close(new_socket);
    t->finished = true;
}

bool check_ip(string ip) {
    if (ip == "") return false;
    string left;
    string right;
    for (int i = 0; i < 3; i++) {
        if (ip.find(".") == string::npos) return false;
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

bool check_path(string path) {
    if (path == "") return false;
    Fs tmp(path);
    return tmp.ok;
}

bool check_port(string port) {
    if (port == "") return false;
    int tmp = stoi(port);
    return tmp > 0 && tmp < 65535;
}

bool check_thread_limit(string thread_limit) {
    int limit = stoi(thread_limit);
    return limit > 0 && limit <= MAX_THREAD_NUM;
}

