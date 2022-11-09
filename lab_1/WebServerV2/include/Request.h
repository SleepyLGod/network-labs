#ifndef SOCKET_REQUEST_H
#define SOCKET_REQUEST_H
#include <string>
#include <map>
using namespace std;

class Request {
public:
     string type; // 请求类型
     string http_version; // http版本
     string url; // 请求url
     map<string, string> header; // 请求头
     Request(string);
};

bool endswith(string A, string B);

#endif //SOCKET_REQUEST_H
