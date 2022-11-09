#ifndef SOCKET_FS_H
#define SOCKET_FS_H
#include "config.h"
#include <string>
#include <map>
#include <fstream>

using namespace std;

class Fs {
public:
    bool ok; // 请求的路径符合要求
    string ab_path; // 绝对路径
    string re_path; // 相对路径
    string file_type; // 文件类型
    ifstream file;
    Fs(string);
    Fs();
    static map<string, string> content_type;
    static string regulate(string);
    static bool check_path(string, string);
};


#endif //SOCKET_FS_H
