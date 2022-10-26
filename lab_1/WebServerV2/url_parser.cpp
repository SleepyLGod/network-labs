#include "url_parser.h"

std::map<std::string, std::string> UrlParser::content_type_ = {
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

/**
 * @brief constructor
 */
UrlParser::UrlParser() = default;

/**
 * @brief constructor
 * @param path
 */
UrlParser::UrlParser(std::string path) {
    this->file_ = std::ifstream(path);
    if (!file_.good()) {
        this->is_ok_ = false;
        return;
    }
    this->is_ok_ = true;
    this->file_type_ = path.substr(path.find_last_of('.') + 1, path.size());
    if (UrlParser::content_type_.find(this->file_type_) == UrlParser::content_type_.end()) { // 如果不存在，则默认认为是文本
        this->file_type_ = UrlParser::content_type_["txt"];
    } else {
        this->file_type_ = UrlParser::content_type_[file_type_];
    }
}

/**
 * @brief process the url path
 * @param path
 * @return string
 */
std::string UrlParser::Handle(std::string path) {
    while(path.find("/./") != std::string::npos) { // 去除所有的.
        std::string left = path.substr(0, path.find("/./"));
        std::string right = path.substr(path.find("/./") + 3, path.size() - path.find('.') - 3);
        path = left + "/" + right;
    }
    while (path.find("/../") != std::string::npos) { // 去除所有的..
        // 如果存在..
        std::string left = path.substr(0, path.find("/../")); // 类似于 /abc/a/.. 会变为 /abc/a/
        std::string right = path.substr(path.find("/../") + 4, path.size() - path.find("/../") - 4); // 左右都没有/
        if (left.empty()) { // 如果只剩下 /
            return ""; // 有问题
        } else {
            left = left.substr(0, left.find_last_of('/') + 1); // 找到上一个/所在的位置
            path = left + right;
        }
    }
    return path;
}

/**
 * @brief check the path of the url
 * @param path
 * @return bool
 */
bool UrlParser::CheckPath(std::string path, std::string base_path) {
    // 检查是否越界
    path = Handle(path);
    if (path.size() < base_path.size()) {
        return false;
    } else {
        if (path.substr(0, base_path.size()) == base_path) {
            return true;
        }
        return false;
    }
}
