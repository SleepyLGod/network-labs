
#ifndef SERVER_H
#define SERVER_H

#include <cstdio>
#include <string>
#include <QThread>
#include <QTextBrowser>
#include <iostream>
#include <sys/socket.h>
#include <cstdlib>
#include <netinet/in.h>
#include <arpa/inet.h>

/**
 * @brief the class of http server configuration
 */
class HttpServer : public QThread{
    Q_OBJECT
public:

    HttpServer(QObject * parent = 0);

    void set_port(int);
    void set_max_thread_num(int);
    void set_ip_to_listen(std::string);
    void set_base_path(std::string);
    void set_all(std::string, std::string, std::string, std::string);
    void Print(std::string s);

    int get_port();
    int get_max_thread_num();
    std::string get_ip_to_listen();
    std::string get_base_path();

    QTextBrowser * output;

    void Run();
    void Stop();
    void ReStart();

signals:
    void print_message(QString);

private:
    bool is_stoped_;
    int port_;
    int max_thread_num_;
    std::string ip_to_listen_;
    std::string base_path_;
    int server_fd_;
};

#endif // SERVER_H
