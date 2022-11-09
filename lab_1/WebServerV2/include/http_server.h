#ifndef SOCKET_HTTP_SERVER_H
#define SOCKET_HTTP_SERVER_H

#include <string>
#include <QThread>
#include <QTextBrowser>
using namespace std;
class http_server : public QThread {
    Q_OBJECT
public:
    http_server(QObject * parent = 0);
    void set_port(int port);
    void set_max_thread_num(int num);
    void set_ip_to_listen(string ip);
    void set_base_path(string path);
    void set_all(string, string, string, string);
    void print(string s);
    int get_port();
    int get_max_thread_num();
    string get_ip_to_listen();
    string get_base_path();

    QTextBrowser * output;

    void run();
    void stop();
    void restart();
signals:
    void print_message(QString);

private:
    bool stoped;
    int port;
    int max_thread_num;
    string ip_to_listen;
    string base_path;
    const string not_find = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/404_dong.html";
    const string bad_request = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/400_dong.html";
    const string index = "/home/dong/Git-repos/network-labs/lab_1/WebServerV1/res/index_dong.html";
    int server_fd;
};


#endif //SOCKET_HTTP_SERVER_H
