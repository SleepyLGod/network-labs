/**
 * @author dong
 * @date 26/10/2022
 */

#ifndef URL_PARSER_H
#define URL_PARSER_H
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "config.h"

/**
 * @brief the util class to parse and process the url
 */
class UrlParser {
public:
    bool is_ok_{}; // 请求的路径是否符合要求
    std::string ab_path_; // 绝对路径
    std::string re_path_; // 相对路径
    std::string file_type_; // 文件类型
    std::ifstream file_;
    explicit UrlParser(std::string); // 防止隐式转换
    UrlParser();
    static std::map<std::string, std::string> content_type_;
    static std::string Handle(std::string path);
    static bool CheckPath(std::string, std::string);
};

#endif // URL_PARSER_H
