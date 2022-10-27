/**
 * @author dong
 * @date 26/10/2022
 */

#pragma once
#ifndef WEBSERVERV1_REQUEST_H
#define WEBSERVERV1_REQUEST_H

#include "iostream"
#include "string"
#include "map"
#include "sstream"

/**
 * @brief the class to process request
 */
class Request {
public:
    std::string request_type_; // type of the request
    std::string http_version_; // http version
    std::string request_url_; // url of the request
    std::map<std::string, std::string> request_header_; // request header

    explicit Request(const std::string&);
};

/**
 * @brief check out if the string a ends with string b
 * @param a
 * @param b
 * @return bool
 */
bool EndsWith(const std::string& a, const std::string& b) {
    if (a.length() >= b.length())
        return (0 == a.compare(a.length() - b.length(), b.length(), b));
    return false;
}

/**
 * @brief constructor
 * @param request
 */
Request::Request(const std::string& request) {
    std::istringstream istringstream(request);
    std::string line;
    getline(istringstream, line); // first line: request line
    std::istringstream words(line); // split the line into several words
    words >> this->request_type_;
    words >> this->request_url_;
    words >> this->http_version_;
    // request header:
    while (getline(istringstream, line, '\n')) {
        if (line == "\r") break;
        std::string key = line.substr(0, line.find_first_of(':'));
        std::string value = line.substr(line.find_first_of(':'), line.size() - line.find_first_of(':') - 1);
        this->request_header_.insert({key, value});
    }
}

#endif //WEBSERVERV1_REQUEST_H
