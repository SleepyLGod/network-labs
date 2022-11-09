#include <cstdlib>
#include <netinet/in.h>

#include "server.h"

int main() {
    std::string ip_to_listen_;
    std::cout << "Please input your ip to be listened: ";
    server_config::ip_to_listen = new char[100];
    std::cin >> server_config::ip_to_listen;
    std::cout << "Please input the port: ";
    std::cin >> server_config::port;
    std::cout << "Please input the max number of the threads: ";
    std::cin >> server_config::max_thread_num;
    int server_fd;
    int new_socket;
    int valread;
    std::mutex m; // 输出日志锁
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    // 创建新的socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // 配置socket参数
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                    & opt, sizeof(opt))) {
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(server_config::ip_to_listen);
    address.sin_port = htons(server_config::port);
    // 绑定端口等
    if (bind(server_fd, (struct sockaddr * ) &address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // 开始监听
    if (listen(server_fd, server_config::max_thread_num) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "* Running on http://" << server_config::ip_to_listen << ":"
                <<  server_config::port << "/ (Press CTRL+C to quit)" << std::endl;

    // TODO: use the modified thread pool I wrote before.
    std::vector<ThreadEncapsulation *> threads_pool; // 简易线程池
    std::vector<bool> threads_status;
    while(true) { // 阻塞监听
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        std::string ip_in = std::string(inet_ntoa(address.sin_addr));
        for (int i = 0; i < threads_pool.size(); i++) {
            if (threads_pool.at(i)->is_finished_) {
                threads_pool.erase(threads_pool.begin() + i);
                i--;
            }
        }
        std::cout << "目前有" << threads_pool.size() << "个连接" << std::endl;
        if (threads_pool.size() < server_config::max_thread_num) { // 如果还可以加入
            ThreadEncapsulation client;
            client.CreateThread(new_socket, ip_in);
            threads_pool.push_back(&client);
            client.is_added_ = true;
        } else { // 如果已经满了，持续等待直到有空闲
            while(true) {
                bool flag = false;
                for (int i = 0; i < threads_pool.size(); i++) {
                    if (threads_pool.at(i)->is_finished_) {
                        threads_pool.erase(threads_pool.begin() + i);
                        i--;
                        flag = true;
                    }
                }
                if (flag) break;
            }
        }

//        std::string ip_in_ = std::string(inet_ntoa(address.sin_addr));
//        read(new_socket, buffer, 1024);
//        printf("%s\n", buffer);
//
//        Request request = Request(std::string(buffer));
//        Response response = Response(request);
//        std::string path = server_config::path + request.request_url_;
//        UrlParser fs;
//        if (request.request_url_ == "/")
//            path = server_config::index;
//        char file_buffer[255];
//        if (!UrlParser::CheckPath(path)) { // 如果检测不通过，访问了上级目录
//            response.set_status(400);
//            fs = UrlParser(server_config::bad_request);
//        } else {
//            fs = UrlParser(path);
//            if (fs.is_ok_) {
//                response.set_status(200);
//            } else {
//                fs = UrlParser(server_config::not_found);
//                response.set_status(404);
//            }
//        }
//
//        /*
//         * 输出日志
//         * */
//        LogPrint(response, request, ip_in);
//        response.AddHeader("Content-Type", fs.file_type_);
//        write(new_socket, response.ToString().c_str(), response.ToString().size()); // 写入返回头
//        // 写入返回主体
//        while(fs.file_.readsome(file_buffer, sizeof(file_buffer)))
//            write(new_socket, file_buffer, fs.file_.gcount());
//        close(new_socket);

    }
}