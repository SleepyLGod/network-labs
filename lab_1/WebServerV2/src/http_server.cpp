#include "../include/http_server.h"
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <mutex>

#include "../include/Request.h"
#include "../include/utils.h"
#include "../include/Fs.h"
#include "../include/my_thread.h"

http_server::http_server(QObject * parent) {
    this->port = PORT;
    this->ip_to_listen = IP_TO_LISTEN;
    this->max_thread_num = MAX_THREAD_NUM;
    this->base_path = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/";
    this->stoped = true;
    this->output = nullptr;
}

string http_server::get_base_path() {
    return this->base_path;
}

string http_server::get_ip_to_listen() {
    return this->ip_to_listen;
}

int http_server::get_max_thread_num() {
    return this->max_thread_num;
}

int http_server::get_port() {
    return this->port;
}

void http_server::set_base_path(string path) {
    if (this->base_path != path)
        this->base_path = path;
}

void http_server::set_ip_to_listen(string ip) {
    if (this->ip_to_listen != ip)
        this->ip_to_listen = ip;
}

void http_server::set_max_thread_num(int num) {
    if (this->max_thread_num != num)
        this->max_thread_num = num;
}

void http_server::set_port(int port) {
    if (port != this->port)
        this->port = port;
}

void http_server::set_all(string ip, string path, string port, string thread_limit) {
    set_ip_to_listen(ip);
    set_base_path(path);
    set_port(stoi(port));
    set_max_thread_num(stoi(thread_limit));
}

void http_server::run() {
//    output->setText("进入run");
    this->stoped = false;
//    print("* Server Started\n");
    cout << "Server Started" << endl;
    int new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { // 创建新的socket
        print("socket failed\n");
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, & opt, sizeof(opt))) { // 配置socket参数
        print("set socket option error\n");
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this->ip_to_listen.c_str());
    address.sin_port = htons(this->port);
    if (bind(server_fd, (struct sockaddr * ) &address, sizeof(address)) < 0) { // 绑定端口等
        print("bind failed\n");
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, this->max_thread_num) < 0) { // 开始监听
        print("listen failed\n");
        perror("listen");
        exit(EXIT_FAILURE);
    }
    print("* Running on http://" + this->ip_to_listen + ":" + to_string(this->port) + "/ (Click Stop button to quit)\n");
    cout << "* Running on http://" << this->ip_to_listen << ":" <<  this->port << "/ (Press CTRL+C to quit)" << endl;
    vector<my_thread *> threads_pool;
    vector<bool> threads_status;
    int count = 0;
    while(true) {
        // 阻塞监听
        if (this->stoped) {
            print("* Server Stoped\n");
            cout << "* Server Stoped" << endl;
            return;
        }
        if ((new_socket = accept(server_fd, (struct sockaddr *) &address, (socklen_t * ) & addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        count++;
        cout << count << endl;
        string ip_in = string(inet_ntoa(address.sin_addr));

        for (int i = 0; i < threads_pool.size(); i++) {
            if (threads_pool.at(i)->finished) {
//                delete threads_pool.at(i);
                threads_pool.erase(threads_pool.begin() + i);
                i--;
            }
        }
        cout << "目前有" << threads_pool.size() << "个连接" << endl;
        if (threads_pool.size() < this->max_thread_num) { // 如果还可以加入
            my_thread client;
            client.create_thread(new_socket, ip_in, this);
            threads_pool.push_back(&client);
            client.added = true;
        } else { // 如果已经满了，持续等待直到有空闲
            while (1) {
                if (this->stoped) return;
                bool flag = false;
                for (int i = 0; i < threads_pool.size(); i++) {
                    if (threads_pool.at(i)->finished) {
                        threads_pool.erase(threads_pool.begin() + i);
                        i--;
                        flag = true;
                    }
                }
                if (flag) break;
            }
        }
    }
}


void http_server::stop() {
    print("* Server Stoped\n");
    this->stoped = true;
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
}

void http_server::restart() {
    cout << "* Server Restarting" << endl;
    this->stoped = true;
    sleep(1);
}

void http_server::print(string s) {
    QString qs = output->toPlainText();
    string tmp = qs.toUtf8().constData();
    QString new_string = QString::fromStdString(tmp + s);
    Q_EMIT print_message(new_string);
}


