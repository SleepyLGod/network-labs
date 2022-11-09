#ifndef SOCKET_RESPONSE_H
#define SOCKET_RESPONSE_H

#include <map>
#include <string>
#include "Request.h"

using namespace std;
class Response {
public:
    map<string, string> header;
    string http_version;
    int status; // 状态码
    string word;  // 状态字


    Response(int status, string http_version);
    Response(Request);
    void add_header(string key, string value);
    void set_status(int status);
    void set_http_version(string http_version);
    string to_string(); // 返回响应的字符串

private:
    const map<int, string> status_words = {
            {200, "OK"},
            {400, "Bad Request"},
            {404, "Not Found"}
    };
};


#endif //SOCKET_RESPONSE_H
