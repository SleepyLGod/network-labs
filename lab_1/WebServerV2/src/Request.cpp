#include "../include/Request.h"
#include "sstream"
#include <iostream>

Request::Request(string request) {
    istringstream iss(request);
    string line;
    getline(iss, line); // 第一行,请求头
    istringstream words(line); // 分解出每一个字段
    words >> this->type;
    words >> this->url;
    words >> this->http_version;
    // 开始读取header

    while(getline(iss, line, '\n')) {
        if (line == "\r") break;
        string key = line.substr(0, line.find_first_of(':'));
        string value = line.substr(line.find_first_of(':'), line.size() - line.find_first_of(':') - 1);
        this->header.insert({key, value}); // 插入键值对
    } // 剩下的iss部分就是body
}

bool endswith(string A, string B) {
    if (A.length() >= B.length())
        return (0 == A.compare (A.length() - B.length(), B.length(), B));
    return false;
}
