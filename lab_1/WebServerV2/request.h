/**
 * @author dong
 * @date 26/10/2022
 */

#pragma once
#ifndef REQUEST_H
#define REQUEST_H

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

    explicit Request(std::string);
};

bool EndsWith(std::string, std::string);

#endif //WEBSERVERV1_REQUEST_H

