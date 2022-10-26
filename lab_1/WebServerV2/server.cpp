#include "server.h"

/**
 * @brief constructor
 */
HttpServer::HttpServer(QObject * parent) {
    this->port_ = 8080;
    this->ip_to_listen_ = server_config::ip_to_listen;
    this->max_thread_num_ = server_config::max_thread_num;
    this->base_path_ = server_config::path;
    this->is_stoped_ = true;
    this->output = nullptr;
}

/**
 * @brief getter
 * @return string
 */
std::string HttpServer::get_base_path() {
    return this->base_path_;
}

/**
 * @brief getter
 * @return string
 */
std::string HttpServer::get_ip_to_listen() {
    return this->ip_to_listen_;
}

/**
 * @brief getter
 * @return int
 */
int HttpServer::get_max_thread_num() {
    return this->max_thread_num_;
}

/**
 * @brief getter
 * @return int
 */
int HttpServer::get_port() {
    return this->port_;
}

/**
 * @brief setter
 * @param path
 */
void HttpServer::set_base_path(std::string path) {
    if (this->base_path_ != path)
        this->base_path_ = path;
//        ReStart();
}

/**
 * @brief setter
 * @param ip
 */
void HttpServer::set_ip_to_listen(std::string ip) {
    if (this->ip_to_listen_ != ip)
        this->ip_to_listen_ = ip;
//        ReStart();
}

/**
 * @brief setter
 * @param num
 */
void HttpServer::set_max_thread_num(int num) {
    if (this->max_thread_num_ != num)
        this->max_thread_num_ = num;
//        ReStart();
}

/**
 * @brief setter
 * @param port
 */
void HttpServer::set_port(int port) {
    if (port != this->port_)
        this->port_ = port;
//        ReStart();
}

/**
 * @brief HttpServer::set_all
 * @param ip
 * @param path
 * @param port
 * @param thread_limit
 */
void HttpServer::set_all(std::string ip, std::string path, std::string port, std::string thread_limit) {
    set_ip_to_listen(ip);
    set_base_path(path);
    set_port(stoi(port));
    set_max_thread_num(stoi(thread_limit));
//    restart();
}

/**
 * @brief run the server
 */
void HttpServer::Run() {
//    output->setText("进入run");
    this->is_stoped_ = false;
    std::cout << "Server Started" << std::endl;
    int new_socket;
    struct sockaddr_in address{};
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};
    // 创建新的socket
    if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        Print("socket failed\n");
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    // 配置socket参数
    if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                    & opt, sizeof(opt))) {
        Print("set socket option error\n");
        perror("setsocketopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr(this->ip_to_listen_.c_str());
    address.sin_port = htons(this->port_);
    // 绑定端口等
    if (bind(server_fd_, (struct sockaddr * ) &address, sizeof(address)) < 0) {
        Print("bind failed\n");
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // 开始监听
    if (listen(server_fd_, this->max_thread_num_) < 0) {
        Print("listen failed\n");
        perror("listen");
        exit(EXIT_FAILURE);
    }
    Print("* Running on http://" + this->ip_to_listen_ + ":" + std::to_string(this->port_) + "/ (Click Stop button to quit)\n");
    std::cout << "* Running on http://" << this->ip_to_listen_ << ":"
                <<  this->port_ << "/ (Press CTRL+C to quit)" << std::endl;
    std::vector<ThreadEncapsulation *> threads_pool;
    std::vector<bool> threads_status;
    int count = 0;
    while(true) {
        if (this->is_stoped_) { // 阻塞监听
            Print("* Server Stoped\n");
            std::cout << "* Server Stoped" << std::endl;
            return;
        }
        if ((new_socket = accept(server_fd_, (struct sockaddr *) &address, (socklen_t * ) & addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        count++;
        std::cout << count << std::endl;
        std::string ip_in = std::string(inet_ntoa(address.sin_addr));

        for (int i = 0; i < threads_pool.size(); i++) {
            if (threads_pool.at(i)->is_finished_) {
                threads_pool.erase(threads_pool.begin() + i);
                i--;
            }
        }
        std::cout << "目前有" << threads_pool.size() << "个连接" << std::endl;
        if (threads_pool.size() < this->max_thread_num_) { // 如果还可以加入
            ThreadEncapsulation client;
            client.CreateThread(new_socket, ip_in);
            threads_pool.push_back(&client);
            client.is_added_ = true;
        } else { // 如果已经满了，持续等待直到有空闲
            while (true) {
                if (this->is_stoped_) return;
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
    }
}

/**
 * @brief stop the server
 */
void HttpServer::Stop() {
    Print("* Server Stoped\n");
    this->is_stoped_ = true;
    shutdown(server_fd_, SHUT_RDWR);
    close(server_fd_);
}

/**
 * @brief rerun the server
 */
void HttpServer::ReStart() {
    std::cout << "* Server Restarting" << std::endl;
    this->is_stoped_ = true;
    sleep(1);
//    this->Run();
}

//void HttpServer::PrintMessage(QString s) {
//    return;
//}

void HttpServer::Print(std::string s) {
//    string origin = output->toPlainText();
    QString qs = output->toPlainText();
    std::string tmp = qs.toUtf8().constData();
    QString new_string = QString::fromStdString(tmp + s);
    Q_EMIT PrintMessage(new_string);
//    std::cout << output->toPlainText().toStdString();
//    this->output->setText("噜啦啦");
}
