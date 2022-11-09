#include "../include/Fs.h"
#include <fstream>

using namespace std;

Fs::Fs() {
    return;
}

Fs::Fs(string path) {
    this->file = ifstream(path);
    if (!file.good()) {
        this->ok = false;
        return;
    }
    this->ok = true;
    file_type = path.substr(path.find_last_of('.') + 1, path.size());
    if (content_type.find(file_type) == content_type.end()) { // 如果不存在，则默认认为是文本
        file_type = content_type["txt"];
    } else {
        file_type = content_type[file_type];
    }
}

string Fs::regulate(string path) {
    while(path.find("/./") != string::npos) { // 去除所有的.
        string left = path.substr(0, path.find("/./"));
        string right = path.substr(path.find("/./") + 3, path.size() - path.find(".") - 3);
        path = left + "/" + right;
    }
    while (path.find("/../") != string::npos) { // 去除所有的..
        // 如果存在..
        string left = path.substr(0, path.find("/../")); // 类似于 /abc/a/.. 会变为 /abc/a/
        string right = path.substr(path.find("/../") + 4, path.size() - path.find("/../") - 4); // 左右都没有/
        if (left.size() == 0) { // 如果只剩下 /
            return ""; // 说明有问题
        } else {
            left = left.substr(0, left.find_last_of("/") + 1); // 找到上一个/所在的位置
            path = left + right;
        }
    }
    return path;
}

bool Fs::check_path(string path, string base_path) { // 检查是否越界
    path = regulate(path);
    if (path.size() < base_path.size()) {
        return false;
    } else {
        if (path.substr(0, base_path.size()) == base_path) return true;
        return false;
    }
}

map<string, string> Fs::content_type = {
        {"png", "image/png"},

        {"gif", "image/gif"},

        {"ico", "image/x-icon"},
        {"cur", "image/x-icon"},

        {"jpg", "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"jfif", "image/jpeg"},
        {"pjpeg", "image/jpeg"},
        {"pjp", "image/jpeg"},

        {"apng", "image/apng"},

        {"svg", "image/svg+xml"},

        {"tif", "image/tiff"},
        {"tiff",  "image/tiff"},
        {"webp", "image/webp"},

        {"txt", "text/plain; charset=utf-8"},
        {"css", "text/css; charset=utf-8"},
        {"html", "text/html; charset=utf-8"}
};
